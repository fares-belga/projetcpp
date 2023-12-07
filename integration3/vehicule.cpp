#include "vehicule.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QString>
///////////////////////////////////////////////////////////////////////
vehicule::vehicule(int id_veh,QString type_veh,QString date_entretien,QString kilometrage,QString image)
{
    this->id_veh=id_veh;
    this->type_veh=type_veh;
    this->date_entretien=date_entretien;
    this->kilometrage=kilometrage;
    this->image=image;
}
//////////////////////////////////////////////////////////////////////////
bool vehicule::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO VEHICULE(id_veh, type_veh, date_entretien, kilometrage, image) VALUES(:id_veh, :type_veh, :date_entretien, :kilometrage, :image)");
    query.bindValue(":id_veh", id_veh);
    query.bindValue(":type_veh", type_veh);
    query.bindValue(":date_entretien", date_entretien);
    query.bindValue(":kilometrage", kilometrage);
    query.bindValue(":image", image);

    bool inserted = query.exec();

    if (inserted) {
        qDebug() << "Record inserted successfully!";
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }

    return inserted;
}

//////////////////////////////////////////////////////////////////////////
QSqlQueryModel * vehicule::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel();

   model->setQuery("select * from vehicule");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_veh"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("type_veh"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("date_entretien"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));


   return model;
}
////////////////////////////////////////////////////////////////////////////
//bool vehicule::supprimerv(int id_veh)
//{
    //QSqlQuery query;

   // query.prepare("delete from vehicule where id_veh=:id_veh");
   // query.bindValue(":id_veh",id_veh);
   // return query.exec();
//}


//////////////////////////////////////////////////////////////////////////////



int vehicule::statistiquesvehicule(QString type_veh)
{
    QSqlQuery query;
    query.prepare("select count(*) from vehicule where type_veh=:type_veh ");
    query.bindValue(":type_veh",type_veh);
    query.exec();
    query.next();

    return query.value(0).toInt();

}

////////////////////////////////////////////////
QSqlQueryModel * vehicule::recherche_vehicule(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from vehicule  where id_veh like '%"+search+"%'or type_veh like '%"+search+"%' or date_entretien like '%"+search+"%' or kilometrage like '%"+search+"%'";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}

////////////////////////////////////////////////////////////////////////////////////
QSqlQueryModel * vehicule::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM vehicule ORDER BY id_veh");
    return model;

}


bool vehicule::incrementNbVeh() {
    QSqlQuery query;
    query.prepare("UPDATE NOMBRE_VEHICULE SET NBR_VEH = NBR_VEH + 1");

    if (!query.exec()) {
        qDebug() << "Failed to increment NBR_VEH in database";
        return false;
    }

    return true;
}

bool vehicule::decrementNbVeh() {
    QSqlQuery query;
    query.prepare("UPDATE NOMBRE_VEHICULE SET NBR_VEH = NBR_VEH - 1");

    if (!query.exec()) {
        qDebug() << "Failed to increment NBR_VEH in database";
        return false;
    }

    return true;
}

