from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
import os

db = SQLAlchemy()

# Modelo da Tabela
class Pessoa(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    nome = db.Column(db.String(100))
    sexo = db.Column(db.String(20))
    data_nascimento = db.Column(db.String(20))
    cidade = db.Column(db.String(100))
    telefone = db.Column(db.String(30))