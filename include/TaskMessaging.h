//
// Created by Ludin Nento on 01/08/21.
//

#ifndef ESP32T_TASKMESSAGING_H
#define ESP32T_TASKMESSAGING_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"


#include <cassert>
#include <memory>
#include <mutex>
#include <utility>


namespace TASKMESSAGING
{

    class QueueInterface
    {
    public:
        const size_t queue_len{0};
        const size_t item_size_bytes{0};

        operator bool() const { return h_queue ? true : false; }

        QueueInterface() = delete;

        template<typename T>
        esp_err_t send(const T& item)
        {
            std::scoped_lock _guard(_send_mutex);


            if (*this) // *this call bool operator or if(h_queue) || if(h_queue.get() != nullprt)
            {
                if(!full())
                {
                    if(pdPASS == xQueueSend(h_queue.get(), &item, 0))
                    {
                        return ESP_OK;
                    }
                    return ESP_FAIL;
                }

                return ESP_ERR_NO_MEM;
            }

            return ESP_ERR_INVALID_STATE;

        }

        template<typename T>
        esp_err_t send_to_front(const T& item)
        {
            std::scoped_lock _guard(_send_mutex);

            if (*this) // *this call bool operator or if(h_queue) || if(h_queue.get() != nullprt)
            {
                if(!full())
                {
                    if(pdPASS == xQueueSendToFront(h_queue.get(), &item, 0))
                    {
                        return ESP_OK;
                    }
                    return ESP_FAIL;
                }

                return ESP_ERR_NO_MEM;
            }
            return ESP_ERR_INVALID_STATE;
        }

        template<typename T>
        esp_err_t receive(T& item)
        {
            std::scoped_lock _guard(_receive_mutex);

            if (*this) // *this call bool operator or if(h_queue) || if(h_queue.get() != nullprt)
            {
                if(!empty())
                {
                    if(pdPASS == xQueueReceive(h_queue.get(), &item, 0))
                    {
                        return ESP_OK;
                    }
                    return ESP_FAIL;
                }

                return ESP_ERR_NOT_FOUND;
            }
            return ESP_ERR_INVALID_STATE;
        }

        template<typename T>
        esp_err_t peak(T& item) {
            std::scoped_lock _guard(_receive_mutex);

            if (*this) // *this call bool operator or if(h_queue) || if(h_queue.get() != nullprt)
            {
                if(!empty())
                {
                    if(pdPASS == xQueuePeek(h_queue.get(), &item, 0))
                    {
                        return ESP_OK;
                    }
                    return ESP_FAIL;
                }

                return ESP_ERR_NOT_FOUND;

            }
            return ESP_ERR_INVALID_STATE;
        }


        size_t n_item_waiting() const
        {
            std::scoped_lock _guard(_send_mutex, _receive_mutex);

            if(*this)
                return uxQueueMessagesWaiting(h_queue.get());

            return 0;
        }

        size_t n_free_space() const
        {
            std::scoped_lock _guard(_send_mutex, _receive_mutex);

            if(*this)
                return uxQueueSpacesAvailable(h_queue.get());

            return 0;
        }

        bool empty() const { return 0 == n_item_waiting(); }
        bool full() const { return 0 == n_free_space(); }
        bool clear()
        {
            std::scoped_lock _guard(_send_mutex, _receive_mutex);

            if(*this)
                return pdPASS == xQueueReset(h_queue.get());

            return false;
        }

    protected:

        QueueInterface(
            std::unique_ptr<QueueDefinition> h_queue,
            const size_t n_item,
            const size_t item_n_bytes) :
            queue_len{n_item},
            item_size_bytes{item_n_bytes},
            h_queue{h_queue}
            {
                assert(0 < n_item);
                assert(0 < item_n_bytes);
            }

        QueueInterface(const QueueInterface& other) :
            queue_len{other.n_item},
            item_size_bytes{other.item_n_bytes},
            h_queue{other.h_queue}
            {}

        std::shared_ptr<QueueDefinition>     h_queue{};
        mutable std::recursive_mutex                _send_mutex{};
        mutable std::recursive_mutex                _receive_mutex{};
    };


    class DynamicQueue : protected QueueInterface
    {
    public:
        DynamicQueue(const size_t n_items, const size_t item_n_bytes) :
                QueueInterface{
            std::move(create_queue_unique_ptr(n_items, item_n_bytes)), n_items, item_n_bytes}
        {}

    private:
        QueueHandle_t create_queue(const size_t n_items, const size_t item_n_bytes)
        {
            return xQueueCreate(n_items, item_n_bytes);
        }

        void delete_queue(QueueHandle_t h)
        {
            std::scoped_lock _guard(_send_mutex, _receive_mutex);
            vQueueDelete(h);

        }

        std::unique_ptr<QueueDefinition> create_queue_unique_ptr(const size_t n_items, const size_t item_n_bytes)
        {
            return {create_queue(n_items, item_n_bytes),
                [this](auto h) { delete_queue(); }};
        }

    };

    template <typename T, size_t n_items>
    class StaticQueue : public QueueInterface
    {
    public:
        StaticQueue(void) :
        QueueInterface{std::move(create_queue_unique_ptr(n_items, sizeof(T))), n_items, sizeof(T)}
        {}

    private:
        QueueHandle_t create_queue(const size_t n_items, const size_t item_n_bytes)
        {
            return xQueueCreateStatic(n_items, item_n_bytes, queue_storage, &queue_control_block);
        }

        void delete_queue(QueueHandle_t h)
        {
            std::scoped_lock _guard(send_mutx, receive_mutx);
            vQueueDelete(h);
        }

        std::unique_ptr<QueueDefinition> create_queue_unique_ptr(const size_t n_items, const size_t item_n_bytes)
        {
            return { create_queue(n_items, item_n_bytes),
                     [this](auto h){ delete_queue(h); }};
        }

        StaticQueue_t queue_control_block{};
        uint8_t       queue_storage[n_items * sizeof(T)]{};
    };

} // TASKMESSAGING
#endif //ESP32T_TASKMESSAGING_H
