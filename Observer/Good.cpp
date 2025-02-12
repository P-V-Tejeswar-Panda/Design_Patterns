#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisplayInterface{
    public:
    virtual void update(double temp, double humidity, double pressure) = 0;
};

class WeatherData{
    private:
    double temperature      = 0;
    double pressure         = 0;
    double humidity         = 0;
    vector<DisplayInterface*> displays;
    public:
    WeatherData(double temp, double humidity, double pressure);
    int subscribe(DisplayInterface* disp);
    void unsubscribe(DisplayInterface *disp);
    double getTemparature(); 
    double getHumidity();
    double getPressure();
    void measurementsChanged();
    ~WeatherData();   
};

class CurrentConditions: public DisplayInterface{
    WeatherData* weatherData = NULL;
    public:
    CurrentConditions(WeatherData* wd){
        this->weatherData = wd;
    }
    void update(double temp, double humidity, double pressure){
        cout << "Current Conditions: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
    void unsubscribe(){
        this->weatherData->unsubscribe(this);
    }
};
class Statistics: public DisplayInterface{
    WeatherData* weatherData = NULL;
    public:
    Statistics(WeatherData* wd){
        this->weatherData = wd;
    }
    void update(double temp, double humidity, double pressure){
        cout << "Statistics: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
    void unsubscribe(){
        this->weatherData->unsubscribe(this);
    }
};
class Forecast: public DisplayInterface{
    WeatherData* weatherData = NULL;
    public:
    Forecast(WeatherData* wd){
        this->weatherData = wd;
    }
    void update(double temp, double humidity, double pressure){
        cout << "Forecast: T: " << temp << " H: " << humidity << " P: " << pressure << endl;
    }
    void unsubscribe(){
        this->weatherData->unsubscribe(this);
    }
};

WeatherData::WeatherData(double temp, double humidity, double pressure){
    this->temperature = temp;
    this->pressure   = pressure;
    this->humidity   = humidity;
}
int WeatherData::subscribe(DisplayInterface* disp){
    this->displays.push_back(disp);
    return 0;
}
void WeatherData::unsubscribe(DisplayInterface *disp){
    vector<DisplayInterface*>::iterator itr = find(this->displays.begin(), this->displays.end(), disp);
    if(itr != this->displays.end()){
        this->displays.erase(itr);
    }
}

double WeatherData::getTemparature(){
    return this->temperature;
}

double WeatherData::getHumidity(){
    return this->humidity;
}

double WeatherData::getPressure(){
    return this->pressure;
}

void WeatherData::measurementsChanged(){
    /* We have to implement this method to support three displays*/
    double temp  = getTemparature();
    double hm    = getHumidity();
    double press = getPressure();
    for(DisplayInterface* disp: displays){
        disp->update(temp, hm, press);
    }
}
WeatherData::~WeatherData(){
    for(DisplayInterface* disp: displays)
        delete disp;
}

int main(void){
    WeatherData wd = WeatherData(2.3, 3.4, 4.5);
    Forecast* fc = new Forecast(&wd);
    wd.subscribe(fc);
    wd.measurementsChanged();
    CurrentConditions* cc = new CurrentConditions(&wd);
    wd.subscribe(cc);
    wd.measurementsChanged();
    cc->unsubscribe();
    wd.measurementsChanged();
}