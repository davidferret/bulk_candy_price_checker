#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define TAX_RATE 1.07
#define DEFAULT_PRICE 1.99


struct Memory {
    char *response;
    size_t size;
};


size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if (ptr == NULL) return 0;

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, total_size);
    mem->size += total_size;
    mem->response[mem->size] = 0;

    return total_size;
}


float fetch_real_price() {
    CURL *curl;
    CURLcode res;
    struct Memory chunk = {malloc(1), 0};

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/chocolate-prices"); // Replace with a real API such as zylalabs
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    if (res != CURLE_OK) {
        printf("Failed to fetch prices, using default $%.2f per bar.\n", DEFAULT_PRICE);
        return DEFAULT_PRICE;
    }


    struct json_object *parsed_json;
    struct json_object *price_obj;
    parsed_json = json_tokener_parse(chunk.response);
    if (json_object_object_get_ex(parsed_json, "price", &price_obj)) {
        return (float)json_object_get_double(price_obj);
    }

    return DEFAULT_PRICE;
}


float calculate_price(int num_bars, float price_per_bar) { // Example of discounts, not needed depending on API used
    float discount = 1.0;
    
    if (num_bars >= 150 && num_bars <= 300) {
        discount = 0.85;
    } else if (num_bars >= 301 && num_bars <= 500) {
        discount = 0.83;
    } else if (num_bars > 500) {
        discount = 0.81;
    }

    float subtotal = num_bars * price_per_bar * discount;
    return subtotal * TAX_RATE;
}

int main(void) {
    int num_bars;
    float price_per_bar = fetch_real_price();

    printf("Enter the number of chocolate bars: ");
    while (scanf("%d", &num_bars) != 1 || num_bars <= 0) {
        printf("Invalid input! Enter a positive number: ");
        while (getchar() != '\n');
    }

    float total_price = calculate_price(num_bars, price_per_bar);
    printf("Total price (including tax): $%.2f\n", total_price);

    return 0;
}
