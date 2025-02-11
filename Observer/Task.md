### Given an propritary object WeatherData, design views for it

#### Given:
```python
class WeatherData:
    def getTemperature() -> double:
    def getHumidity() -> double:
    def getPressure() -> double:
    def measurementsChanged() -> None: # this method is called whenever there is a change in
                                       # in the weather conditions. We have to implement this
                                       # method to support three views:
                                       # 1. CurrentConditions, 2. Statistics, 3. forecast
                                       # this method is called whenever there is a change in
                                       # the weather.
```