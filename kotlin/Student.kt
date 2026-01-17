class Student(val stu_number: String, val grade: Int, name: String, age: Int) : Person(stu_number, age) {
    init {
        println("Student number is $stu_number")
        println("Grade is $grade")
    }
    constructor(name: String, age: Int) : this("", 0, name, age) {
    }
    constructor() : this("", 0)
}