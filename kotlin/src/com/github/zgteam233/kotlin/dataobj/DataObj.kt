package com.github.zgteam233.kotlin.dataobj

fun main() {
    val cellphone1 = Cellphone("三星 Samsung", 1299.99)
    val cellphone2 = Cellphone("三星 Samsung", 1299.99)
    println("cellphone1: $cellphone1")
    println("cellphone1 等于 cellphone2 ${cellphone1 == cellphone2}")
    Singleton.singletonTest()
}