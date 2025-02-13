/*
Problem with Good.cpp:
1. Lets say in future the Subject added new state data,
for ex: lets say windspeed measurements
and we have new observers that require windspeed information.
Now we will have to modify the display interface which in turn requires
changing all the displays(Observers) now imagine if the displays are
owned by diffrent teams or worse, different companies! It would be a disaster!.

2. Lets say all displays don't have all information and we have thousands of
state data variables! All displays will be flooded with data that they
don't need.

Solution:
Part - 1:
Let's have a generic update() method without any arguments
Part - 2:
lets add getter functions to our subject for each state variable so that
the observers can pick only those data that they need via the getter functions.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DisplayInterface{
    public:
    // Let's have a generic update method
    virtual void update() = 0;
};

class WeatherData{
    protected:
    double temperature      = 0;
    double pressure         = 0;
    double humidity         = 0;
    vector<DisplayInterface*> displays;
    public:
    WeatherData();
    int subscribe(DisplayInterface* disp);
    void unsubscribe(DisplayInterface *disp);
    double getTemparature(); 
    double getHumidity();
    double getPressure();
    void measurementsChanged();
    void setMeasurements(double temp, double humidity, double pressure);
    ~WeatherData();   
};

class CurrentConditions: public DisplayInterface{
    WeatherData* weatherData = NULL;
    public:
    CurrentConditions(WeatherData* wd){
        this->weatherData = wd;
    }
    void update(){
        cout << "Current Conditions: T: " << weatherData->getTemparature() << " H: " << weatherData->getHumidity() << " P: " << weatherData->getPressure() << endl;
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
    void update(){
        cout << "Statistics: T: " << weatherData->getTemparature() << " H: " << weatherData->getHumidity() << " P: " << weatherData->getPressure() << endl;
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
    void update(){
        cout << "Forecast: T: " << weatherData->getTemparature() << " H: " << weatherData->getHumidity() << " P: " << weatherData->getPressure() << endl;
    }
    void unsubscribe(){
        this->weatherData->unsubscribe(this);
    }
};

WeatherData::WeatherData(){
    setMeasurements(0, 0, 0);
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

void WeatherData::setMeasurements(double temp, double humidity, double pressure){
    this->temperature = temp;
    this->pressure   = pressure;
    this->humidity   = humidity;
    measurementsChanged();
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
    for(DisplayInterface* disp: displays){
        disp->update();
    }
}
WeatherData::~WeatherData(){
    for(DisplayInterface* disp: displays)
        delete disp;
}

int main(void){
    WeatherData wd = WeatherData();
    Forecast* fc = new Forecast((WeatherData*)&wd);
    wd.subscribe(fc);
    wd.setMeasurements(1.0, 2.0, 3.0);
    CurrentConditions* cc = new CurrentConditions((WeatherData*)&wd);
    wd.subscribe(cc);
    wd.setMeasurements(4.0, 5.0, 6.0);
    cc->unsubscribe();
    wd.setMeasurements(7.0, 8.0, 9.0);

    // Now we have a new version of subject that has windSpeed &
    // a new observer, HurricaneDisplay that can use windSpeed but doesn't require anything else



}
