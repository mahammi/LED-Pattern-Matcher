// Samantha and Maham ECE 198 @ Waterloo

#define BUTTON_BLINK
// #define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>
#include "ece198.h"

void game_lost(void);
void light_all_pins(int ledBlue, int ledRed, int ledGreen, int ledYellow);

int main(void)
{

    HAL_Init(); // initialize the Hardware Abstraction Layer
    HAL_Delay(2000);

    __HAL_RCC_GPIOA_CLK_ENABLE(); 
    __HAL_RCC_GPIOB_CLK_ENABLE(); 
    __HAL_RCC_GPIOC_CLK_ENABLE(); 

    // initialize the pins to be input / output
    InitializePin(GPIOB, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_10 ,GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED
    InitializePin(GPIOA, GPIO_PIN_9 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLDOWN, 0);  // on-board button
    InitializePin(GPIOB, GPIO_PIN_9 | GPIO_PIN_8, GPIO_MODE_INPUT, GPIO_PULLDOWN, 0); 

    SerialSetup(9600);

    // B
    int ledBlue = GPIO_PIN_3 ;
    int ledRed = GPIO_PIN_5 ;
    int ledGreen = GPIO_PIN_4 ;
    int ledYellow = GPIO_PIN_10 ;

    int buttonBlue = GPIO_PIN_6 ; // A
    int buttonRed = GPIO_PIN_9 ; // A
    int buttonGreen = GPIO_PIN_9 ; // B
    int buttonYellow = GPIO_PIN_8 ; // B

    // Let player know game is ready
    light_all_pins(ledBlue, ledRed, ledGreen, ledYellow);

    // Seed
    while(true){
        if (HAL_GPIO_ReadPin(GPIOA, buttonBlue)){
            srand(HAL_GetTick()); // seeding srand
            break;
        }
    }

    HAL_Delay(1000);

    // Generate LED array pattern
    int number_in_LED_array = 5;
    int LED_array [number_in_LED_array];

    for (int i = 0 ; i < number_in_LED_array ; i++){
        LED_array[i] = (int) (rand() % 4) + 1;
    }

    int current_LED = 1; //determines how much of the pattern is shown

    while (current_LED != number_in_LED_array + 1){
        // shows the pattern
        for (int i = 0; i < current_LED; i++){

            HAL_Delay(800);

            if (LED_array[i] == 1) { // blue
                HAL_GPIO_WritePin(GPIOB, ledBlue, 1);
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOB, ledBlue, 0); 
                HAL_Delay(200);
            } else if (LED_array[i] == 2){ // red
                HAL_GPIO_WritePin(GPIOB, ledRed, 1);
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOB, ledRed, 0); 
                HAL_Delay(200);
            } else if (LED_array[i] == 3) { // green
                HAL_GPIO_WritePin(GPIOB, ledGreen, 1);
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOB, ledGreen, 0); 
                HAL_Delay(200);
            } else if (LED_array[i] == 4){
                HAL_GPIO_WritePin(GPIOB, ledYellow, 1);
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOB, ledYellow, 0); 
                HAL_Delay(200);
            }
        } // game has finished showing the pattern

        
        
        // user must copy pattern
        for (int k=0; k< current_LED; k++){
            bool theyClickedRight = false ;

            while (true){
                if (HAL_GPIO_ReadPin(GPIOA, buttonBlue)){ // blue means value should be 0
                    if (LED_array[k] != 1){ // clicked the wrong button
                        game_lost();
                        break;
                    }
                    
                    theyClickedRight = true ;

                    HAL_GPIO_WritePin(GPIOB, ledBlue, 1);
                    HAL_Delay(800);
                    HAL_GPIO_WritePin(GPIOB, ledBlue, 0); 
                    HAL_Delay(200);
                }

                else if (HAL_GPIO_ReadPin(GPIOA, buttonRed)){
                    if (LED_array[k] != 2){ // clicked the wrong button
                        game_lost();
                        break;
                    }

                    theyClickedRight = true ;

                    HAL_GPIO_WritePin(GPIOB, ledRed, 1);
                    HAL_Delay(800);
                    HAL_GPIO_WritePin(GPIOB, ledRed, 0); 
                    HAL_Delay(200);
                }

                else if (HAL_GPIO_ReadPin(GPIOB, buttonGreen)){
                    if (LED_array[k] != 3){ // clicked the wrong button
                        game_lost();
                        break;
                    }

                    theyClickedRight = true ;

                    HAL_GPIO_WritePin(GPIOB, ledGreen, 1);
                    HAL_Delay(800);
                    HAL_GPIO_WritePin(GPIOB, ledGreen, 0); 
                    HAL_Delay(200);
                }

                else if (HAL_GPIO_ReadPin(GPIOB, buttonYellow)){
                    if (LED_array[k] != 4){ // clicked the wrong button
                        game_lost();
                        break;
                    }

                    theyClickedRight = true ;

                    HAL_GPIO_WritePin(GPIOB, ledYellow, 1);
                    HAL_Delay(800);
                    HAL_GPIO_WritePin(GPIOB, ledYellow, 0); 
                    HAL_Delay(200);
                }

                // Exit while loop if guessed correctly 
                if (theyClickedRight){
                    break ;
                }
            } 
        } 

        // they move on to the next round
        current_LED++;
    }
    light_all_pins(ledBlue, ledRed, ledGreen, ledYellow);
}

void game_lost(void){
    int ledRed = GPIO_PIN_5 ;

    while (true){
        HAL_GPIO_TogglePin(GPIOB, ledRed);
        HAL_Delay(300);
        HAL_GPIO_TogglePin(GPIOB, ledRed);
        HAL_Delay(300);
    }
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}

void light_all_pins(int ledBlue, int ledRed, int ledGreen, int ledYellow){
    HAL_GPIO_WritePin(GPIOB, ledBlue, 1);
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, ledBlue, 0); 
    HAL_GPIO_WritePin(GPIOB, ledRed, 1);
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, ledRed, 0); 
    HAL_GPIO_WritePin(GPIOB, ledGreen, 1);
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, ledGreen, 0); 
    HAL_GPIO_WritePin(GPIOB, ledYellow, 1);
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, ledYellow, 0); 
}
