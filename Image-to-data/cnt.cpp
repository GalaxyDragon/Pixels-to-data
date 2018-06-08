#include "cnt.h"

cnt::cnt(QObject *parent) : QObject(parent)
{

}
void cnt::table_resize()
    {
            int a = this->hi->value();
            int b = this->we->value();
            this->tab->clear();
            this->tab->setColumnCount(b);
            this->tab->setRowCount(a);

            tab->horizontalHeader()->setDefaultSectionSize(50);
            tab->verticalHeader()->setDefaultSectionSize(50);
            for(int i=0; i<a;i++){
                for(int j=0; j<b;j++){

                    QPushButton* butt = new QPushButton();
                    butt->setStyleSheet("QPushButton:checked { background-color: rgb(0,0,0);}");
                    butt->setFlat(true);


                    butt->setChecked(false);
                    butt->setCheckable(true);

                    this->tab->setCellWidget(i,j,butt);

                }
            }
        }
void cnt::cell_resize()
{
    int a = this->cell->value();
    this->tab->verticalHeader()->setDefaultSectionSize(a);
    this->tab->horizontalHeader()->setDefaultSectionSize(a);
}
void cnt::count()
{
    int a = this->tab->columnCount();
    int b = this->tab->rowCount();
    QString prefix = "";
    if (this->bin->isChecked()){
        prefix = "0b";
    }else{
        prefix = "0x";
    }
    QString kos[16] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
    QString resultat="{";
    for(int i=0; i<a;i++){
        int res = 0;
        QString buff = prefix;
        for(int j=0; j<b;j++){
            QPushButton* c(qobject_cast<QPushButton*>(this->tab->cellWidget(j,i)));
            if(this->bin->isChecked()){
                if(c->isChecked()){
                    buff+="1";
                }else{
                    buff+="0";
                }
            }else{
            res+=c->isChecked();
            if (((j%4==3)||(j==(b-1)))){
                buff+=kos[res];
                res=0;
            }else{
                res<<=1;
            }

            }
        }
        resultat+=buff;
        if(i!=(a-1)){
        resultat+=", ";
        }
    }
    resultat+="}";
    text->setText(resultat);
}

void cnt::copy(){
    QString a = text->toPlainText();
    QClipboard* buf = QApplication::clipboard();
    buf->setText(a);
}
