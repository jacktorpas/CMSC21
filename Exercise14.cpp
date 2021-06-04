#include <iostream>
#include <iomanip>

using namespace std;

class Package {
    protected:
        double weight, cost;
    public:
        Package(){
            weight = 0;
            cost = 0;
        }

        Package(double wt, double cost){
            this->weight = wt;
            this->cost = cost;
        }

        double calculateCost(){
            return this->weight * this->cost;
        }
};

class TwoDayPackage : public Package {
    double flatFee;
    public:
        TwoDayPackage(){
            weight = 0;
            cost = 0;
            flatFee = 0;
        }

        TwoDayPackage(double wt, double cost, double fFee){
            this->weight = wt;
            this->cost = cost;
            this->flatFee = fFee;
        }

        double calculateCost(){
            return Package::calculateCost() + this->flatFee;
        }
};

class OvernightPackage : public Package {
    double overnightFee;
    public:
        OvernightPackage(){
            weight = 0;
            cost = 0;
            overnightFee = 0;
        }

        OvernightPackage(double wt, double cost, double oFee){
            this->weight = wt;
            this->cost = cost;
            this->overnightFee = oFee;
        }

        double calculateCost(){
            return Package::calculateCost() + (this->overnightFee * this->weight);
        }
};

int main(){
    double weight, cost, fFee, overnightFee;
    cin >> weight >> cost >> fFee >> overnightFee;
    Package pck(weight, cost);
    TwoDayPackage twoDay(weight, cost, fFee);
    OvernightPackage ovn(weight, cost, overnightFee);

    cout << setprecision(2) << fixed << pck.calculateCost() << " " << twoDay.calculateCost() << " " << ovn.calculateCost() << endl;
}

