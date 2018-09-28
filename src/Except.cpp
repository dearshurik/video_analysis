/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Except.cpp
 * Author: kuznetsov
 * 
 * Created on September 28, 2018, 1:00 PM
 */

#include "Except.h"

Except::Except(const std::string& desc) 
    : description(desc)
{
}

Except::Except(const Except& orig) {
    description = orig.description;
}

Except::~Except() {
}

