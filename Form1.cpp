#include <stddef.h> 
#include "pch.h"
#include "Form1.h"
using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Windows::Forms;

 System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
    // 1. Definimos la cadena de conexión (Poné tu contraseña y el nombre de tu base de datos)
    String^ datosConexion = "server=127.0.0.1;uid=root;pwd=1284;database=comercial";

    // 2. Creamos el objeto de conexión
    MySqlConnection^ conexion = gcnew MySqlConnection(datosConexion);

    try {
        // 3. Intentamos abrir la base de datos
        conexion->Open();

        // Si llega acá, ¡el conector funciona perfecto!
        MessageBox::Show("¡Conexión exitosa a MySQL! El conector funciona de 10.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);

        // Cerramos la conexión para no dejarla abierta
        conexion->Close();

    }
    catch (Exception^ ex) {
        // Si hay algún problema (contraseña mal puesta, puerto bloqueado, etc.) salta acá
        MessageBox::Show("Error al conectar: " + ex->Message, "Error de Conexión", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}


