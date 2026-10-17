#include "practicaproyecto.h"
#include <QPushButton>
#include <QString>

practicaproyecto::practicaproyecto(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	connect(ui.btnIniciarSesion, &QPushButton::clicked,
		this, &practicaproyecto::validarSesion);

}

practicaproyecto::~practicaproyecto()
{}


string convertirMinuscula(string texto) {//FUNCION AUXILIAR
	for (int i = 0;i < texto.size(); i++) {
		texto[i] = tolower(texto[i]);
	}
	return texto;
}

bool practicaproyecto::validarSesion(vector<string> nombresRegistrados, vector<string> contrasennasRegistrados){//FUNCION AUXILIAR
	string nombre = ui.txtNombre->text().toStdString();
	string contrasenna = ui.txtContrasenna->text().toStdString();

	for (int i = 0; i < nombresRegistrados.size(); i++) {
		if (nombresRegistrados[i] == convertirMinuscula(nombre) && convertirMinuscula(contrasenna) == contrasennasRegistrados[i]) {
			return true;
		}
	}
	return false;
}