const char version[] = "1.1.0";

const int rxPin = 3;
const int txPin = 4; // This pin is not used

typedef enum rotaryMovement{
  ROTARY_UP,
  ROTARY_DOWN
};

typedef enum tinfoType{
  TINFO_HP,
  TINFO_HC,
  TINFO_PAPP,
  TINFO_IINST,
  TINFO_LAST
};