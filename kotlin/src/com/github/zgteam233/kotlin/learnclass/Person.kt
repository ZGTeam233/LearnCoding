package com.github.zgteam233.kotlin.learnclass

open class Person(val name: String, val age: Int) {
    fun eat() {
        println("$name 正在吃饭。他 $age 岁了。")
    }
}