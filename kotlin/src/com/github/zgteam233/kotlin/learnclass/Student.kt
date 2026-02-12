package com.github.zgteam233.kotlin.learnclass

class Student(val sno: String = "", val grade: Int = 0, name: String = "", age: Int = 0) : Person(name, age), Study {
    override fun readBooks() {
        println("$name 正在阅读。")
    }
}