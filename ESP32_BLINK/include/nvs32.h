//
// Created by Ludin Nento on 31/07/21.
//

#ifndef ESP32T_NVS32_H
#define ESP32T_NVS32_H

#include <cstring>

#include "nvs_flash.h"
#include "esp_err.h"
#include "nvs.h"


namespace NVS
{
    class Nvs
    {
        const char* const       _log_tag{nullptr};
        nvs_handle_t            handle{};
        const char* const       partition_name{nullptr};

    public:

        constexpr Nvs(const char* const partition_name = "nvs")
        : _log_tag{partition_name},
        partition_name{partition_name} {}

        [[nodiscard]] esp_err_t init()
        { return _open(partition_name, handle); }

        template<typename T>
        [[nodiscard]] esp_err_t get(const char* const key, T& output)
        { size_t len = 1; return _get_buffer(handle, key, &output, len); }

        template<typename T>
        [[nodiscard]] esp_err_t set(const char* const key, const T& input)
        { return _set_buffer(handle, key, &input, 1); }

        template<typename T>
        [[nodiscard]] esp_err_t verify(const char* const key, const T& input)
        { return _verify_buffer(handle, key, &input, 1); }

        template<typename T>
        [[nodiscard]] esp_err_t get_buffer(const char* const key, T* output, size_t& len)
        { return _get_buffer(handle, key, output, len); }

        template<typename T>
        [[nodiscard]] esp_err_t set_buffer(const char* const key, const T* input, const size_t len)
        { return _set_buffer(handle, key, input, len); }

        template<typename T>
        [[nodiscard]] esp_err_t verify_buffer(const char* const key, const T* input, const size_t len)
        { return _verify_buffer(handle, key, input, len); }

    private:
        [[nodiscard]] static esp_err_t _open(const char* const partition_name, nvs_handle_t& handle)
        {
            return nvs_open(partition_name, NVS_READWRITE, &handle);
        }

        template<typename T>
        [[nodiscard]] static esp_err_t _get(nvs_handle_t handle, const char* const key, T& output)
        {
            size_t n_bytes{sizeof(T)};

            if (nullptr == key || 0 == strlen(key))
                return ESP_ERR_INVALID_ARG;
            else
                return _get_buffer(handle, key, &output, n_bytes);

        }

        template<typename T>
        [[nodiscard]] static esp_err_t _set(nvs_handle_t handle, const char* const key, T& input)
        {
            size_t n_bytes{sizeof(T)};

            if (nullptr == key || 0 == strlen(key))
                return ESP_ERR_INVALID_ARG;
            else
            {
                esp_err_t status{_set_buffer(handle, key, &input, n_bytes)};

                if (ESP_OK ==  status) status |= nvs_commit(handle);

                if (ESP_OK ==  status) status |= _verify(handle, key, &input, n_bytes);

                return status;
            }
        }

        template<typename T>
        [[nodiscard]] static esp_err_t _verify(nvs_handle_t handle, const char* const key, T& input)
        {
            T val_in_nvs{};
            esp_err_t status{_get(handle, key, val_in_nvs)};

            if (ESP_OK == status)
            {
                if (input == val_in_nvs)
                    return ESP_OK;
                else
                    ESP_FAIL;
            }
            else
                return status;

        }

        // Important : length of num items of type T (not necessarily num bytes)
        template<typename T>
        [[nodiscard]] static esp_err_t _get_buffer(nvs_handle_t handle, const char* const key, T* output, size_t& len)
        {
            size_t n_bytes{sizeof(T) * len};

            if (nullptr == key || 0 == strlen(key) || nullptr == output || 0 == len)
                return ESP_ERR_INVALID_ARG;
            else
            {

                const esp_err_t status = nvs_get_blob(handle, key, output, &n_bytes);
                len = n_bytes / sizeof(T);

                return status;
            }

        }

        template<typename T>
        [[nodiscard]] static esp_err_t _set_buffer(nvs_handle_t handle, const char* const key, const T* input,  const size_t len)
        {

            esp_err_t status{ESP_OK};

            if (nullptr == key || 0 == strlen(key) || nullptr == input || 0 == len)
                status =  ESP_ERR_INVALID_ARG;
            else
            {
                status = nvs_set_blob(handle, key, input, sizeof(T) * len);
                if(ESP_OK == status)
                    status = nvs_commit(handle);

                if(ESP_OK == status)
                    status = _verify_buffer(handle, key, input, len);
            }

            return status;

        }

        template<typename T>
        [[nodiscard]] static esp_err_t _verify_buffer(nvs_handle_t handle, const char* const key, const T* input, const size_t len)
        {
            esp_err_t status{ESP_OK};

            T* buf_in_nvs = new T[len]{};
            size_t n_item_in_nvs = len;

            if (buf_in_nvs)
            {
                status = _get_buffer(handle, key, buf_in_nvs, n_item_in_nvs);
                if(ESP_OK == status)
                {
                    if (len == n_item_in_nvs)
                    {
                        if(0 != memcmp(input, buf_in_nvs, len * sizeof(T)))
                        {
                            status = ESP_FAIL;
                        }
                    }
                    else
                        status = ESP_ERR_NVS_INVALID_LENGTH;
                }

                delete[] buf_in_nvs;
            }
            else
                status = ESP_ERR_NO_MEM;

            return status;
        }

    };


}


#endif //ESP32T_NVS32_H
