// Полюбин Арсений
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <limits>
#include <ios>


std::ostream& operator<<(std::ostream& out, const std::pair<float, float>& fig) {
    std::cout << "(" << fig.first << "," << fig.second << ")";
    return out;
}

class Figure {
public:
    float get_area() {
        return std::abs((coordinates_[0].first*coordinates_[1].second + coordinates_[1].first*coordinates_[2].second + coordinates_[2].first*coordinates_[3].second + coordinates_[3].first*coordinates_[0].second) -
                        (coordinates_[1].first*coordinates_[0].second + coordinates_[2].first*coordinates_[1].second + coordinates_[3].first*coordinates_[2].second + coordinates_[0].first*coordinates_[3].second))/2;
    }
    std::pair<float, float> get_centre() {
        return centre_;
    }
    void print() {
        std::cout << coordinates_[0] << coordinates_[1] << coordinates_[2] << coordinates_[3];
    }
protected:
    virtual void get_coordinates(){}
protected:
    std::pair<float, float> centre_;
    std::pair<float, float> coordinates_[4];
};

class Square : public Figure {
public:
    Square(std::pair<float, float> centre, float h) {
        centre_ = centre;
        h_ = h;
        get_coordinates();
    }
protected:
    void get_coordinates() override {
        coordinates_[0].first = centre_.first - h_/2;
        coordinates_[0].second = centre_.second + h_/2;

        coordinates_[1].first = centre_.first + h_/2;
        coordinates_[1].second = centre_.second + h_/2;

        coordinates_[2].first = centre_.first + h_/2;
        coordinates_[2].second = centre_.second - h_/2;

        coordinates_[3].first = centre_.first - h_/2;
        coordinates_[3].second = centre_.second - h_/2;
    }
private:
    float h_;
};

class Rectangle : public Figure {
public:
    Rectangle(std::pair<float, float> centre, float h, float wide) {
        centre_ = centre;
        h_ = h;
        wide_ = wide;
        get_coordinates();
    }
protected:
    void get_coordinates() override {
        coordinates_[0].first = centre_.first - wide_/2;
        coordinates_[0].second = centre_.second + h_/2;

        coordinates_[1].first = centre_.first + wide_/2;
        coordinates_[1].second = centre_.second + h_/2;

        coordinates_[2].first = centre_.first + wide_/2;
        coordinates_[2].second = centre_.second - h_/2;

        coordinates_[3].first = centre_.first - wide_/2;
        coordinates_[3].second = centre_.second - h_/2;
    }
private:
    float h_;
    float wide_;
};

class Trapeze: public Figure {
public:
    Trapeze(std::pair<float, float> centre, float down_base, float up_base, float h) {
        centre_ = centre;
        down_base_ = down_base;
        up_base_ = up_base;
        h_ = h;
        get_coordinates();
    }
protected:
    void get_coordinates() override {
        coordinates_[0].first = centre_.first - up_base_/2;
        coordinates_[0].second = centre_.second + h_/2;

        coordinates_[1].first = centre_.first + up_base_/2;
        coordinates_[1].second = centre_.second + h_/2;

        coordinates_[2].first = centre_.first + down_base_/2;
        coordinates_[2].second = centre_.second - h_/2;

        coordinates_[3].first = centre_.first - down_base_/2;
        coordinates_[3].second = centre_.second - h_/2;
    }
private:
    float h_;
    float down_base_;
    float up_base_;
};

int main() {
    int type;
    std::vector<Figure> figures;
    while (true) {
        std::cout << "Введите тип фигуры: (1) - квадрат, (2) - прямоугольник, (3) - трапеция, (4) - Вывод общей площади фигур" << "\n";
        std::cin >> type;
        if (std::cin.eof()) {
            break;
        }
        if (type == 1) {
            std::pair<float, float> centre;
            float h;
            std::cout << "Введите поочередно координаты центра и высоту" << "\n";
            std::cin >> centre.first >> centre.second >> h;
            if (std::cin.fail()) {
                std::cout << "Введите верное значение координат!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
                continue;
            }
            Square tmp(centre, h);
            figures.push_back(tmp);
            std::cout << "квадрат" << '\n' << "площадь: " << tmp.get_area() << '\n' << "центр: " << tmp.get_centre() << '\n' << "координаты вершин: ";
            tmp.print();
            std::cout << std::endl;
        }
        else if (type == 2) {
            std::pair<float, float> centre;
            float wide;
            float h;
            std::cout << "Введите поочередно координаты центра, высоту, ширину" << "\n";
            std::cin >> centre.first >> centre.second >> h >> wide;
            if (std::cin.fail()) {
                std::cout << "Введите верное значение координат!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Rectangle tmp(centre, h, wide);
            figures.push_back(tmp);
            std::cout << "Прямоугольник" << '\n' << "Площадь: " << tmp.get_area() << '\n' << "центр: " << tmp.get_centre() << '\n' << "координаты: ";
            tmp.print();
            std::cout << std::endl;
        }
        else if (type == 3) {
            std::pair<float, float> centre;
            float down_base;
            float up_base;
            float h;
            std::cout << "Введите поочередно координаты центра, нижнее основание,верхнее основание, высоту" << "\n";
            std::cin >> centre.first >> centre.second >> down_base >> up_base >> h;
            if (std::cin.fail()) {
                std::cout << "Введите верное значение координат!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            Trapeze tmp(centre, down_base, up_base, h);
            figures.push_back(tmp);
            std::cout << "трапеция" << '\n' << "площадь: " << tmp.get_area() << '\n' << "центр: " << tmp.get_centre() << '\n' << "координаты: ";
            tmp.print();
            std::cout << std::endl;
        }
        else
            if (type == 4) {
                unsigned long total_area = 0;
                for (int i = 0; i < figures.size(); ++i) {
                    total_area += figures[i].get_area();
                }
                std::cout << "Общая площадь: " << total_area << std::endl;
                return 0;
            }

        else {
            std::cout << "Неверно введён тип фигуры!" << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

}
