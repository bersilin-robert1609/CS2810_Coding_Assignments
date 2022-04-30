#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Line
{
    public: //y = ax+b
        double a, b;
        double x1, x2, y1, y2;
        Line(double x1, double y1, double x2, double y2);
        double intersect(Line &l);
        bool isIntersect(Line &l);
};

Line::Line(double x1, double y1, double x2, double y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->a = (y2-y1)/(x2-x1);
    this->b = y1 - (this->a)*x1;
}

double Line::intersect(Line &l)
{
    if((this->a-l.a) != 0) return (l.b - this->b)/(this->a - l.a);
    else return -1;
}

bool Line::isIntersect(Line &l)
{
    if(this->a != l.a) return true;
    else{
        if(this->b != l.b) return true;
        else return false;
    }
}

class Polygon
{
    protected:
        int type;
        int poly_type;
        double perimeter_value;
        vector<Line> lines;
        vector<pair<double, double>> points;
        vector<double> angles;
    public:
        double perimeter();
        virtual bool isPolygon()=0;
        friend bool areSame(Polygon &p1, Polygon &p2);
};

double Polygon::perimeter()
{
    int total = 0;
    if(type == 1){
        for(int i=0; i<points.size(); i++)
        {
            total+=sqrt(pow(points[i].first-points[(i+1)%points.size()].first, 2) + pow(points[i].second-points[(i+1)%points.size()].second, 2));
        }
    }
    else{
        for(int i=0; i<lines.size(); i++)
        {
            total += sqrt(pow(lines[i].x1-lines[i].x2, 2) + pow(lines[i].y1-lines[i].y2, 2));
        }
    }
    perimeter_value = total;
    return total;
}

class Triangle : public Polygon
{
    private:
        
    public:
        Triangle(vector<pair<double, double>> &p, vector<double> &a);
        Triangle(vector<Line> &l);
        virtual bool isPolygon();
        bool isEquilateral(){
            if(type == 0){
                double dist[3];
                for(int i=0; i<3; i++)
                {
                    dist[i] = sqrt(pow(points[i].first-points[(i+1)%3].first, 2) + pow(points[i].second-points[(i+1)%3].second, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 && abs(dist[1] - dist[2]) <= 0.01) return true;
                else return false;
            }else{
                double dist[3];
                for(int i=0; i<3; i++)
                {
                    dist[i] = sqrt(pow(lines[i].x1-lines[i].x2, 2) + pow(lines[i].y1-lines[i].y2, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 && abs(dist[1] - dist[2]) <= 0.01) return true;
                else return false;
            }
        }
        bool isIsosceles(){
            if(type == 0){
                double dist[3];
                for(int i=0; i<3; i++)
                {
                    dist[i] = sqrt(pow(points[i].first-points[(i+1)%3].first, 2) + pow(points[i].second-points[(i+1)%3].second, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 || abs(dist[1] - dist[2]) <= 0.01) return true;
                else return false;
            }else{
                double dist[3];
                for(int i=0; i<3; i++)
                {
                    dist[i] = sqrt(pow(lines[i].x1-lines[i].x2, 2) + pow(lines[i].y1-lines[i].y2, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 || abs(dist[1] - dist[2]) <= 0.01) return true;
                else return false;
            }
        }
        bool isRightAngled(){
            if(type == 0){
                if(abs(angles[0] - 90) <= 0.01 || abs(angles[1] - 90) <= 0.01 || abs(angles[2] - 90) <= 0.01) return true;
                else return false;
            }else{
                double dist[3];
                for(int i=0; i<3; i++)
                {
                    dist[i] = sqrt(pow(lines[i].x1-lines[i].x2, 2) + pow(lines[i].y1-lines[i].y2, 2));
                }
                int max_dist_index = 0;
                for(int i=0; i<3; i++)
                {
                    if(dist[i] > dist[max_dist_index]) max_dist_index = i;
                }
                if(pow(dist[max_dist_index], 2) - pow(dist[(max_dist_index+1)%3], 2) - pow(dist[(max_dist_index+2)%3], 2) <= 0.01) return true;
                else return false;
            }
        }
};

Triangle::Triangle(vector<pair<double, double>> &p, vector<double> &a)
{
    points = p;
    angles = a;
    type = 0;
    poly_type = 1;
}

Triangle::Triangle(vector<Line> &l)
{
    lines = l;
    type = 1;
    poly_type = 1;
}

bool Triangle::isPolygon()
{
    if(type == 1)
    {
        if(lines[0].isIntersect(lines[1]) == -1) return false;
        if(lines[0].isIntersect(lines[2]) == -1) return false;
        if(lines[1].isIntersect(lines[2]) == -1) return false;
        return true;
    }else
    {
        return true;
    }
}

class Quadrilateral : public Polygon
{
    public:
        Quadrilateral(vector<pair<double, double>> &p, vector<double> &a);
        Quadrilateral(vector<Line> &l);
        virtual bool isPolygon(){return false;} 
        bool isSquare()
        {
            if(type == 0){
                double dist[4];
                for(int i=0; i<4; i++)
                {
                    dist[i] = sqrt(pow(points[i].first-points[(i+1)%4].first, 2) + pow(points[i].second-points[(i+1)%4].second, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 && abs(dist[1] - dist[2]) <= 0.01 && abs(dist[2] - dist[3]) <= 0.01) return true;
                else return false;
            }else{
                double dist[4];
                for(int i=0; i<4; i++)
                {
                    dist[i] = sqrt(pow(lines[i].x1-lines[i].x2, 2) + pow(lines[i].y1-lines[i].y2, 2));
                }
                if(abs(dist[0] - dist[1]) <= 0.01 && abs(dist[1] - dist[2]) <= 0.01 && abs(dist[2] - dist[3]) <= 0.01) return true;
                else return false;
            }
        } 
        bool isRectangle();
        bool isRhombus(){return false;} 
        bool isParallelogram(){return false;} 
};

Quadrilateral::Quadrilateral(vector<pair<double, double>> &p, vector<double> &a)
{
    points = p;
    angles = a;
    type = 0;
    poly_type = 2;
}

Quadrilateral::Quadrilateral(vector<Line> &l)
{
    lines = l;
    type = 1;
    poly_type = 2;
}

class Pentagon : public Polygon
{
    public:
        Pentagon(vector<pair<double, double>> &p, vector<double> &a);
        Pentagon(vector<Line> &l);
        virtual bool isPolygon(){return false;} 

};

Pentagon::Pentagon(vector<pair<double, double>> &p, vector<double> &a)
{
    points = p;
    angles = a;
    type = 0;
    poly_type = 3;
}

Pentagon::Pentagon(vector<Line> &l)
{
    lines = l;
    type = 1;
    poly_type = 3;
}

int main()
{
    int n;
    cin>>n;

    vector<Polygon*> polygons;
    vector<int> ids;

    for(int j=0; j<n; j++)
    {
        int k, i, ID;
        cin>>k; //edges of the polygon
        cin>>i;
        vector<pair<double, double>> points;
        vector<double> angles;
        vector<Line> lines;
        if(i == 0)
        { 
            for(i=0; i<k; i++)
            {
                double x1, y1, x2, y2;
                cin>>x1>>y1>>x2>>y2;
                Line l(x1, y1, x2, y2);
                lines.push_back(l);
            }

            if(k == 3){
                Polygon* t = new Triangle(lines);
                polygons.push_back(t);
            }
            else if(k == 4){
                Polygon* q = new Quadrilateral(lines);
                polygons.push_back(q);
            }
            else if(k == 5){
                Polygon* p = new Pentagon(lines);
                polygons.push_back(p);
            }
        }else
        {    
            for(i=0; i<k; i++)
            {
                double x1, y1, angle;
                cin>>x1>>y1>>angle;
                points.push_back(make_pair(x1, y1));
                angles.push_back(angle);
            }

            if(k == 3)
            {
                Polygon* t = new Triangle(points, angles);
                polygons.push_back(t);
            }
            else if(k == 4)
            {
                Polygon* q = new Quadrilateral(points, angles);
                polygons.push_back(q);
            }
            else if(k == 5)
            {
                Polygon* p = new Pentagon(points, angles);
                polygons.push_back(p);
            }
        }
        cin>>ID;
        ids.push_back(ID);
    }

    for(int i=0; i<n; i++)
    {
        if(polygons[i]->isPolygon()) cout<< polygons[i]->perimeter()<<endl;
        else cout<<"INVALID POLYGON"<<endl;
    }

    int Q;
    cin>>Q;
    while(Q--)
    {
        int opcode;
        cin>>opcode;
        if(opcode == 1)
        {
            int id1, id2;
            cin id1>>id2;
            cout<<(isSame(polygons[id1], polygons[id2]) ? "YES" : "NO")<<endl;
        }
    }


    return 0;
}