/* Andrea Sisto */
/* Bias Panel Firmware V1 */

#include <Joystick.h>
#include "biasPanel.h"


void setup() 
{
  Serial.begin(115200);

  //pin setup
  for(int i = 2; i<29; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  Joystick.begin();

  //set all buttons off
  for(int i = 0; i<32; i++)
  {
    Joystick.setButton(i, 0);
  }

}



void loop() 
{
  //local vars
  uint8_t i = 0;

  //buttons
  const uint8_t butPins[6] = {BUT1, BUT2, BUT3, BUT4, BUT5, BUT6};
  uint8_t butNew[6] = {1,1,1,1,1,1};
  uint8_t butOld[6] = {1,1,1,1,1,1};

  //switches
  uint8_t swiData[2][2];    //up, dn
  const uint8_t swiPins[2][2] = {{WIP_UP, WIP_DN}, 
                                {LIT_UP, LIT_DN}};
  const uint8_t swiButtons[2][3] = {{WIP_UP_BTN, WIP_MID_BTN, WIP_DN_BTN}, //{UP, MID, DN}
                                    {LIT_UP_BTN, LIT_MID_BTN, LIT_DN_BTN}};

  //selector
  uint8_t threePosData[2][2]; 
  const uint8_t threePosPins[2][2] = {{BRAK_1, BRAK_2}, 
                                     {TC_1, TC_2}};

  uint8_t twoPosData[2]; 
  uint8_t twoPosCase[2];                                   
  const uint8_t twoPosPins[2] = {ERS, ARB};

  uint8_t selectorCase[4];

  const uint8_t togglePins[4][2] = {{BRAK_UP, BRAK_DN}, {TC_UP, TC_DN}, {ERS_UP, ERS_DN}, {ARB_UP, ARB_DN}};
  uint8_t toggleNew[4][2];
  uint8_t toggleOld[4][2];

  const uint8_t toggleButtons[4][3][2] = {
    { {BIAS_UP, BIAS_DN}, {ABS_UP, ABS_DN}, {MIG_UP, MIG_DN} },
    { {TC_LVL_UP, TC_LVL_DN}, {TC_SLIP_UP, TC_SLIP_DN}, {TC_CUT_UP, TC_CUT_DN} },
    { {ERS_POW_UP, ERS_POW_DN}, {0, 0}, {ERS_REC_UP, ERS_REC_DN}  },
    { {ARB_F_UP, ARB_F_DN}, {0, 0}, {ARB_B_UP, ARB_B_DN}  }
    };





  while(1)
  {
    //buttons
    for (i = 0; i<6; i++)
    {
      butNew[i] = digitalRead(butPins[i]);  //read current
      if(butNew[i] < butOld[i]) //button pressed
      {
        Joystick.setButton(i, 1);
      }
      if(butNew[i] > butOld[i])  //button released
      {
        Joystick.setButton(i, 0);
      }
      butOld[i] = butNew[i];
    }

    //switches
    for(i = 0; i<2; i++)
    {
      swiData[i][0] = digitalRead(swiPins[i][0]); //up
      swiData[i][1] = digitalRead(swiPins[i][1]); //dn

      if(swiData[i][0] < swiData[i][1]) //switch up
      {
        Joystick.setButton(swiButtons[i][0], 1);
        Joystick.setButton(swiButtons[i][1], 0);
        Joystick.setButton(swiButtons[i][2], 0);
      }
      else if(swiData[i][0] > swiData[i][1]) //switch down
      {
        Joystick.setButton(swiButtons[i][0], 0);
        Joystick.setButton(swiButtons[i][1], 0);
        Joystick.setButton(swiButtons[i][2], 1);
      }
      else //mid
      {
        Joystick.setButton(swiButtons[i][0], 0);
        Joystick.setButton(swiButtons[i][1], 1);
        Joystick.setButton(swiButtons[i][2], 0);
      }
    }

    //3 pos selectors
    for(int i = 0; i<2; i++)
    {
      threePosData[i][0] = digitalRead(threePosPins[i][0]);
      threePosData[i][1] = digitalRead(threePosPins[i][1]);

      if(threePosData[i][0] == 1) selectorCase[i] = LEFT;
      else if(threePosData[i][1] == 1) selectorCase[i] = RIGHT;
      else selectorCase[i] = CENTER;
    }

    //2 pos selectors
    for(i = 0; i<2; i++)
    {
      twoPosData[i] = digitalRead(twoPosPins[i]);

      if(twoPosData[i] == 0) selectorCase[i+2] = LEFT;
      else selectorCase[i+2] = RIGHT;
    }


    //toggle
    for(i = 0; i<4; i++)
    {
      toggleNew[i][0] = digitalRead(togglePins[i][0]);  //up
      toggleNew[i][1] = digitalRead(togglePins[i][1]);  //dn

      if(toggleNew[i][0] < toggleOld[i][0]) //press up
      {
        Joystick.setButton(toggleButtons[i][selectorCase[i]][0], 1); //up 
      }
      if(toggleNew[i][0] > toggleOld[i][0]) //release up
      {
        Joystick.setButton(toggleButtons[i][selectorCase[i]][0], 0); //up 
      }

      if(toggleNew[i][1] < toggleOld[i][1]) //press dn
      {
        Joystick.setButton(toggleButtons[i][selectorCase[i]][1], 1); //dn 
      }
      if(toggleNew[i][1] > toggleOld[i][1]) //release dn
      {
        Joystick.setButton(toggleButtons[i][selectorCase[i]][1], 0); //dn 
      }

      toggleOld[i][0] = toggleNew[i][0];
      toggleOld[i][1] = toggleNew[i][1];
    }

    delay(10);
  }
  






}
