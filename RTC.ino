//setting the RTC to generate a clock signal of 1HZ at sq output
void setSQW(uint8_t value) {
      Wire.beginTransmission(DS1307_CTRL_ID);
      Wire.write(7);
      Wire.write(value);
      Wire.endTransmission();
}

//Fetches the current hour from the RTC (24hr format)
int currentTime()
{
  if (RTC.read(tm)) {
    return tm.Hour;
  }  

}
