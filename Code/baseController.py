import baseModel as Model
import baseView as View


def performInsert(userChoice):
    print("Enter values for " + userChoice + " and separate them with commas")
    insval = View.getSplitInput()

    conn = Model.makerSession()
    if userChoice == "Classroom":
        res = Model.Classroom(number=insval[0], buildingnumber=insval[1])
        conn.add(res)
        conn.commit()
    elif userChoice == "Group":
        res = Model.Group(code=insval[0], number=insval[1], capacity=insval[2])
        conn.add(res)
        conn.commit()
    elif userChoice == "Lector":
        res = Model.Lector(name=insval[0], surname=insval[1])
        conn.add(res)
        conn.commit()
    elif userChoice == "Subject":
        res = Model.Subject(name=insval[0])
        conn.add(res)
        conn.commit()
    elif userChoice == "Student":
        res = Model.Student(name=insval[0], surname=insval[1], group_id=insval[2])
        conn.add(res)
        conn.commit()
    elif userChoice == "Student_Base":
        res = Model.Student(class_id=insval[0], subject_id=insval[1], lector_id=insval[2], group_id=insval[3])
        conn.add(res)
        conn.commit()
    conn.close()


def performDelete(userChoice):
    print("Enter ID in " + userChoice + " table")

    insval = View.getInput(None)

    conn = Model.makerSession()
    if userChoice == "Classroom":
        res = conn.query(Model.Classroom).filter(Model.Classroom.class_id == insval).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Group":
        res = conn.query(Model.Group).filter(Model.Group.group_id == insval).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Lector":
        res = conn.query(Model.Lector).filter(Model.Lector.lector_id == insval).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Subject":
        res = conn.query(Model.Subject).filter(Model.Subject.subject_id == insval).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Student":
        res = conn.query(Model.Student).filter(Model.Student.student_id == insval).first()
        conn.delete(res)
        conn.commit()
    elif userChoice == "Student_Base":
        res = conn.query(Model.Student_Base).filter(Model.Student_Base.conect_id == insval).first()
        conn.delete(res)
        conn.commit()
    conn.close()


def performEdit(userChoice):
    print("Enter ID in " + userChoice + " table")
    obID = View.getInput(None)
    print("Enter values for " + userChoice + " and separate them with commas")
    insval = View.getSplitInput()

    conn = Model.makerSession()
    if userChoice == "Classroom":
        res = conn.query(Model.Classroom).filter(Model.Classroom.class_id == obID).first()
        res.number = insval[0]
        res.buildingnumber = insval[0]
        conn.commit()
    elif userChoice == "Group":
        res = conn.query(Model.Group).filter(Model.Group.groupt_id == obID).first()
        res.code = insval[0]
        res.number = insval[1]
        res.capacity = insval[2]
        conn.commit()
    elif userChoice == "Lector":
        res = conn.query(Model.Lector).filter(Model.Lector.lector_id == obID).first()
        res.name = insval[0]
        res.surname = insval[1]
        conn.commit()
    elif userChoice == "Subject":
        res = conn.query(Model.Subject).filter(Model.Subject.subject_id == obID).first()
        res.name = insval[0]
        conn.commit()
    elif userChoice == "Student":
        res = conn.query(Model.Student).filter(Model.Student.student_id == obID).first()
        res.name = insval[0]
        res.surname = insval[1]
        res.group_id = insval[2]
        conn.commit()
    elif userChoice == "Student_Base":
        res = conn.query(Model.Student_Base).filter(Model.Student_Base.conect_id == obID).first()
        res.class_id = insval[0]
        res.subject_id = insval[1]
        res.lector_id = insval[2]
        res.group_id = insval[3]
        conn.commit()

    conn.close()


def firstScreen():
    View.showMainMenu()
    setMenuChoice = View.getInput(None)
    setCHoiceTable = View.getInput(" Choose table to perform operation: ")

    if setMenuChoice == '1':
        performInsert(setCHoiceTable)
    elif setMenuChoice == '2':
        performDelete(setCHoiceTable)
    elif setMenuChoice == '3':
        performEdit(setCHoiceTable)

