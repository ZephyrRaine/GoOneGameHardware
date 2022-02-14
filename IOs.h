
#define DEBOUNCE 10

extern int led;

class Input
{
  public:
  Input();
  void Compute(bool);
  bool Value;   //la valeur ON ou OFF stable
  bool Previous;
  bool PulseON; //front montant à ON
  bool PulseOFF;// front descendant à OFF
  private:
  int Counter;
};

Input::Input()
{
  Value=false;
  PulseON=false;
  PulseOFF=false;
  Counter=0;
  Previous=false;
};

void Input::Compute(bool Val)
{
  Previous=Value;
  if(Val) Counter=DEBOUNCE;
  else 
  {
    Counter--;
    if (Counter <0) Counter=0;
  }
  if (Counter >0) 
  {
    Value=true;
    digitalWrite(led, HIGH);
  }
  else 
  {
    Value=false;
    digitalWrite(led, LOW);
  }
  
  if(Value && !Previous) PulseON=true;
  else PulseON= false;
  if(!Value && Previous) PulseOFF=true;
  else PulseOFF= false;
  
};
