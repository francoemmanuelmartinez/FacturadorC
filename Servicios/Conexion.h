#pragma once

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Servicios {
    public ref class Conexion {
    public:
        MySqlConnection^ con;

        void conectar() {
            String^ connStr = "Server=localhost;Database=comercial;Uid=root;Pwd=1284;SSL Mode=None;AllowPublicKeyRetrieval=true;";
            con = gcnew MySqlConnection(connStr);
            con->Open();
        }
    };
}
