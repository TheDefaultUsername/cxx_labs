/*
 Задание на лабораторную работу №1 по С++
 Тема: Классы и объекты.
 Задание.
 - Создать простой класс.
 - Создать конструкторы и деструктор
 - Создать простой метод
 - Создать несколько объектов этого класса разными способами.
 ( в статике, на стеке, на куче)
 - Продемонстрировать порядок работы конструкторов и деструкторов.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

class Item {
         int _type;
         int _amount;
         double _status;
    public:
        Item():
            _type(0),_amount(1),_status(1.0)
        {}
        Item(const Item &item) 
        {
            _type=item._type;
            _amount=item._amount;
            _status=item._status;
        }
        Item(int amount, int type, double status):
            _type(type),_amount(amount),_status(status)
        {}

        Item& Corrupt(double value)
        {
            _status=_status-value;
            if (_status<0) {
                _amount=0;
            }
            if (_status<0.01) {
                _status=0.01;
            }
            return *this;
        }
        Item& Repair(double value)
        {
            _status=_status+value;
            if (_status>1.0) {
                _status=1.0;
            }
            return *this;
        }
        Item& ChangeType(int type)
        {
            _type=type;
            return *this;
        }

        Item& operator= (const Item &item)
        {
            _type=item._type;
            _amount=item._amount;
            _status=item._status;
            return *this;
        }
        Item& operator+ (int amount)
        {
            _amount=_amount+amount;
            return *this;
        }
        Item& operator++ ()
        {
            _amount++;
            return *this;
        }
        
        bool operator== (const Item &item);

        friend std::ostream& operator<< (std::ostream& stream, const Item &item) {
            stream << "Item:\nAmount: " << item._amount << "\nType: " << item._type << "\nStatus: " << item._status << "\n";
        }

        ~Item()
        {}
};

int main() {
    
}

