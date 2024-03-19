#pragma once

#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include <string>
using namespace std;

typedef struct 
{
	string surname;
	string name;
	string phone;
	string address;
} PhoneBook;

#endif // !PHONE_BOOK_H