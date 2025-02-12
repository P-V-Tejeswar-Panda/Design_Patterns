#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Good Design Decision #1:
We start by formalizing the interface for the observer.
This will help with two things
1. All observers recieve the state change information in a single well-defined way.
   this will help add new observers dynamically as long as they implement is interface.
   Without this dynamic dispatch won't be possible.
2. Loose coupling, the subject has a well-defined and limited view of the observer.
*/
class DisplayInterface{
    public:
    virtual void update(double temp, double humidity, double pressure) = 0;
};

class WeatherData{
    private:
    double temperature      = 0;
    double pressure         = 0;
    double humidity         = 0;
    /*
    Good Design Decision #2:
        having a dynamic list of diplays and subscribe and unsubscribe
        methods let you 
        1. add and remove new observers at runtime.
        2. Doesn't require code change in Subject.
    */
    vector<DisplayInterface*> displays;
    public:
    WeatherData(double temp, double humidity, double pressure);
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
        // having a pointer to the WeatherData object helps to
        // move unsubscribe logic inside the Display.
        // If we didn't have a pointer inside this class, cannot take the decision
        // of unsubscribing to the Subject inside the class.
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
    setMeasurements(temp, humidity, pressure);
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
    wd.setMeasurements(1.0, 2.0, 3.0);
    CurrentConditions* cc = new CurrentConditions(&wd);
    wd.subscribe(cc);
    wd.setMeasurements(4.0, 5.0, 6.0);
    cc->unsubscribe();
    wd.setMeasurements(7.0, 8.0, 9.0);
}