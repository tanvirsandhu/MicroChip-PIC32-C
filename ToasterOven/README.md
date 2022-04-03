In this program, the user can use the controller kit as a toaster oven using an implementation of Finite State Machines.

On startup, the user picks between three modes, and depending on the modes, certain variables will be able to be adjusted by the user using the buttons and pressing them for a certain duration of time. The three modes are:

  -Bake mode: Both temperature and time are configurable, with temperature  defaulting to 350 degrees F and time to 0:01. Switching between temp and 
    time  can  be  done  by  holding  BTN3  for  >  1s  (defined  as  LONG_PRESS). Whichever  is  selected  has  an  indicator  beside  its  label  and         both  top  and  bottom heating elements are visibly on when cooking in bake mode.
    
  -Toast mode: Only the time can be configured in this mode, and the temperature  is  not  displayed.  There  is  no  selector  indicator  on  the display. 
    Only the bottom heating elements come on in toast mode. 
    
  -Broil mode: The  temperature  is  fixed  at  500  degrees  F  and  only  time  is configurable in this mode. The temperature is displayed in broil mode.     Again, the input selector indicator is not displayed. Only the top heating elements come on in broil mode.  


