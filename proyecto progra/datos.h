#pragma once
#include <QList>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include "Cliente.h"
#include "Producto.h"

inline QList<Cliente> clientes;
inline QList<Producto> productos;
inline Cliente usuarioActual;  // variable global para almacenar el usuario actual
inline int siguienteIdCliente = 1;   // id que recibirá el próximo usuario

inline QString rutaArchivo(const QString& nombre)
{
    QString carpeta = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(carpeta);   // crea la carpeta si no existe
    return carpeta + "/" + nombre;
}

// ---------------------------------------------------------------
// Funciones genéricas: sirven para cualquier clase T que tenga
//   QJsonObject T::toJson() const
//   void        T::fromJson(const QJsonObject&)
//   y constructor por defecto
// ---------------------------------------------------------------
template <typename T>
inline void guardarLista(const QList<T>& lista, const QString& nombreArchivo)
{
    QJsonArray arreglo;
    for (const T& elemento : lista)
        arreglo.append(elemento.toJson());

    QFile archivo(rutaArchivo(nombreArchivo));
    if (archivo.open(QIODevice::WriteOnly)) {
        archivo.write(QJsonDocument(arreglo).toJson());
        archivo.close();
    }
}

template <typename T>
inline void cargarLista(QList<T>& lista, const QString& nombreArchivo)
{
    lista.clear();
    QFile archivo(rutaArchivo(nombreArchivo));
    if (!archivo.open(QIODevice::ReadOnly))
        return;   // aún no existe el archivo: primera ejecución

    QJsonDocument doc = QJsonDocument::fromJson(archivo.readAll());
    archivo.close();

    for (const QJsonValue& valor : doc.array()) {
        T elemento;
        elemento.fromJson(valor.toObject());
        lista.append(elemento);
    }
}

// ---------------------------------------------------------------
// Atajos por clase (misma interfaz que antes)
// ---------------------------------------------------------------
inline void guardarClientes() { guardarLista(clientes, "clientes.json"); }
inline void cargarClientes() { cargarLista(clientes, "clientes.json"); }

inline void guardarProductos() { guardarLista(productos, "productos.json"); }
inline void cargarProductos() { cargarLista(productos, "productos.json"); }


// Opcional: para guardar/cargar todo de una vez
inline void guardarTodo() { guardarClientes(); guardarProductos(); }
inline void cargarTodo() { cargarClientes();  cargarProductos(); }