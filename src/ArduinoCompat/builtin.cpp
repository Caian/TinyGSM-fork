#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void tgsm_yield()
{
    vTaskDelay(1);
}

void tgsm_delay(unsigned long ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

unsigned long tgsm_millis()
{
    return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

/*bool tgsm_isdigit(char)
{

}*/
