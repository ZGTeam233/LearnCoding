package com.github.zgteam233.kotlin.classnull

fun main() {
    val student1 = Student("a123", 5, "Jack", 19)
    val student2 = Student(name = "John", age = 23)
    doStudy(null)
    student2.eat()
}
fun doStudy(study: Study?) {
    study?.readBooks()
    study?.doHomework()
}