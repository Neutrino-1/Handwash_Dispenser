void setSQW(uint8_t value) {
      Wire.beginTransmission(DS1307_CTRL_ID);
      Wire.write(7);
      Wire.write(value);
      Wire.endTransmission();
}

int currentTime()
{
  if (RTC.read(tm)) {
    return tm.Hour;
  }  

}
