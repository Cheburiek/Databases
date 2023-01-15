import sqlalchemy
from sqlalchemy import create_engine
from sqlalchemy import MetaData, Table, Column, Integer, String, ForeignKey, DateTime, Boolean
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref
from sqlalchemy.orm import sessionmaker

metadata = MetaData(schema="public")
Base = declarative_base()
engine = create_engine('postgresql://postgres:35171418@localhost/University', echo=True)


class Classroom(Base):
    __tablename__ = 'Classroom'

    class_id = Column(Integer, primary_key=True)
    number = Column(Integer)
    buildingnumber = Column(Integer)


class Group(Base):
    __tablename__ = 'Group'
    group_id = Column(Integer, primary_key=True)
    code = Column(String(50))
    number = Column(Integer)
    capacity = Column(Integer)


class Lector(Base):
    __tablename__ = 'Lector'
    lector_id = Column(Integer, primary_key=True)
    name = Column(String(50))
    surname = Column(String(50))


class Subject(Base):
    __tablename__ = 'Subject'
    subject_id = Column(Integer, primary_key=True)
    name = Column(String(50))


class Student(Base):
    __tablename__ = 'Student'
    student_id = Column(Integer, primary_key=True)
    name = Column(String(50))
    surname = Column(String(50))
    group_id = Column(Integer, ForeignKey('Group.group_id'))

class Student_Base(Base):
    __tablename__ = 'Student_Base'
    conect_id = Column(Integer, primary_key=True)
    class_id = Column(Integer, ForeignKey('Classroom.class_id'))
    subject_id = Column(Integer, ForeignKey('Subject.subject_id'))
    lector_id = Column(Integer, ForeignKey('Lector.lector_id'))
    group_id = Column(Integer, ForeignKey('Group.group_id'))

makerSession = sessionmaker(bind=engine)
