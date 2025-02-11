#include <iostream>
#include <vector>
using namespace std;

class DisplayInterface{
    public:
    virtual void update(double temp, double humidity, double pressure) = 0;
};

class CurrentConditions: public DisplayInterface{
    public:
    void update(double temp, double humidity, double pressure){
        cout << "Current Conditions: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
};
class Statistics: public DisplayInterface{
    public:
    void update(double temp, double humidity, double pressure){
        cout << "Statistics: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
};
class Forecast: public DisplayInterface{
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
    vector<DisplayInterface*> displays; 
    public:
    WeatherData(double temp, double humidity, double pressure){
        this->temperature = temp;
        this->pressure   = pressure;
        this->humidity   = humidity;
    }
    int subscribe(DisplayInterface* disp){
        this->displays.push_back(disp);
        return 0;
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
        for(DisplayInterface* disp: displays){
            disp->update(temp, hm, press);
        }
    }
    ~WeatherData(){
        for(DisplayInterface* disp: displays)
            delete disp;
    }
};

int main(void){
    WeatherData wd = WeatherData(2.3, 3.4, 4.5);
    wd.subscribe(new Forecast());
    wd.measurementsChanged();
    wd.subscribe(new CurrentConditions());
    wd.measurementsChanged();
}