#include <iostream>
using namespace std;

class CurrentConditions{
    public:
    void update(double temp, double humidity, double pressure){
        cout << "Current Conditions: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
};
class Statistics{
    public:
    void update(double temp, double humidity, double pressure){
        cout << "Statistics: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
};
class Forecast{
    public:
    void update(double temp, double humidity, double pressure){
        cout << "Forecast: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
};

class WeatherData{
    private:
    double temperature      = 0;
    double pressure         = 0;
    double humidity         = 0;
    CurrentConditions currentDisp;
    Statistics        statisticsDisp;
    Forecast          forecastDisp; 
    public:
    WeatherData(double temp, double humidity, double pressure){
        this->temperature = temp;
        this->pressure   = pressure;
        this->humidity   = humidity;
        this->currentDisp       = CurrentConditions();
        this->statisticsDisp    = Statistics();
        this->forecastDisp      = Forecast();
    }

    double getTemparature(){
        return this->temperature;
    }

    double getHumidity(){
        return this->humidity;
    }

    double getPressure(){
        return this->pressure;
    }

    void measurementsChanged(){
        /* We have to implement this method to support three displays*/
        double temp  = getTemparature();
        double hm    = getHumidity();
        double press = getPressure();
        // Bad Design Choice #1:
        //      We have hardcoded the Displays. If in future a new display is added
        //      we will have to edit this function.
        // Bad Design Choice #2:
        //      All these displays have a common interface:
        //          They all use the update method and the list if arguments and order
        //          is identical.
        //      But we haven't formalized it and are not using it.
        // 
        this->currentDisp.update(temp, hm, press);
        this->forecastDisp.update(temp, hm, press);
        this->statisticsDisp.update(temp, hm, press);
    }
};

int main(void){
    WeatherData wd = WeatherData(2.3, 3.4, 4.5);
    wd.measurementsChanged();
    wd.measurementsChanged();
}