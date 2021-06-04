#include <iostream>
#include <iomanip>

using namespace std;

class Point {
    public:
        float x, y;

        Point(){
            x = 0;
            y = 0;
        }

        Point(int a, int b){
            this->x = a;
            this->y = b;
        }

        Point setCoordinates(float a, float b){
            this->x = a;
            this->y = b;
        }
};

class Rectangle {
    private:
        Point topLeft, bottomRight;
    public:
        Rectangle(){
            topLeft.setCoordinates(0, 0);
            bottomRight.setCoordinates(0, 0);
        }

        Rectangle(Point a, Point b){
            this->topLeft = a;
            this->bottomRight = b;
        }

        Rectangle(int a, int b, int c, int d){
            topLeft.setCoordinates(a, b);
            bottomRight.setCoordinates(c, d);
        }

        void setPoints(Point a, Point b){
            this->topLeft = a;
            this->bottomRight = b;
        }

        float area(){
            return (topLeft.x - bottomRight.x) * (topLeft.y - bottomRight.y);
        }

        float perimeter(){
            return 2 * ((bottomRight.x - topLeft.x) + (bottomRight.y - topLeft.y));
        }

        Point centerPoint(){
            Point pt;
            pt.setCoordinates(bottomRight.x - ((bottomRight.x - topLeft.x) / 2), 
                bottomRight.y - ((bottomRight.y - topLeft.y) / 2));
            return pt;
        }

        bool square(){
            if((topLeft.x - bottomRight.x) == (topLeft.y - bottomRight.y)) return true;
            else return false;
        }

        void display(){
            cout << '\n';
            for(int i = 0; i <= bottomRight.y; i++){
                for(int j = 0; j <= bottomRight.x; j++){
                    if(((j == topLeft.x || j == bottomRight.x) && i >= topLeft.y) || 
                        ((i == topLeft.y || i == bottomRight.y) && j >= topLeft.x)) cout << "# ";
                    else cout << "  ";
                }
                cout << '\n';
            }
        }
};

int main(){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    Rectangle rct(a, b, c, d);

    cout << '\n';
    cout << "Area: " << rct.area() << '\n';
    cout << "Perimeter: " << rct.perimeter() << '\n';
    cout << "Center: " << "(" << setprecision(2) << fixed << rct.centerPoint().x << ", " << rct.centerPoint().y << ")";
    cout << "\nSquare: ";
    if(rct.square()) cout << "Yes";
    else cout << "No";
    rct.display();
}