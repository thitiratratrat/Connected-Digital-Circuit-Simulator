//#pragma once
//WireWidget *w = new WireWidget(this->parentW);// might have to change parent
//int xPos = 0;
//int yPos = 0;
//int xDPos = 0;
//int yDPos = 0;
//Connector *clicked1 = NULL; //x is lesser
//Connector *clicked2 = NULL;
//if (parentW->clickedWidget->x() <= parentW->clickedWidget2->x()) {
//	xPos = parentW->clickedWidget->mapToGlobal(parentW->clickedWidget->pos()).x();
//	//xPos = parentW->clickedWidget->x();
//	clicked1 = parentW->clickedWidget;
//	clicked2 = parentW->clickedWidget2;
//}
//else {
//	//xPos = parentW->clickedWidget2->x();
//	xPos = parentW->clickedWidget2->mapToGlobal(parentW->clickedWidget2->pos()).x();
//	clicked1 = parentW->clickedWidget2;
//	clicked2 = parentW->clickedWidget;
//}
////check if labelD needs to be initialized
//if (parentW->clickedWidget->y() != parentW->clickedWidget2->y()) {
//	yPos = clicked2->mapToGlobal(clicked2->pos()).y();
//	xDPos = clicked1->mapToGlobal(clicked1->pos()).x();
//	yDPos = clicked1->mapToGlobal(clicked1->pos()).y();
//	//yPos = clicked2->y();
//	//xDPos = clicked1->x;
//	//yDPos = clicked1->y();
//}
//else {
//	yPos = parentW->clickedWidget->mapToGlobal(parentW->clickedWidget->pos()).y();
//	//yPos = parentW->clickedWidget->y();
//}
//
//QPoint localW;
//localW.setX(xPos);
//localW.setY(yPos);
//
//int xW = w->mapFromGlobal(localW).x() + CONNECTORSIZE - 2;
//int yW = w->mapFromGlobal(localW).y() + CONNECTORSIZE / 2 - 2;
//
//w->setStyleSheet("background-color: blue;");
//
//if (parentW->clickedWidget->y() == parentW->clickedWidget2->y()) {
//	//- BTNDELETESIZE - CONNECTORSIZE / 2 - 2
//	w->setGeometry(w->mapFromGlobal(localW).x() + CONNECTORSIZE - 2, w->mapFromGlobal(localW).y(), abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH + BTNDELETESIZE);
//	//w->setGeometry(xPos + CONNECTORSIZE -2, yPos + CONNECTORSIZE/2 - 2, abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH );
//	//w->setGeometry(xPos, yPos, abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH);
//}
//else if (parentW->clickedWidget->x() == parentW->clickedWidget2->x())
//w->setGeometry(xDPos, yDPos, 100, 100);
////w->setGeometry(xDPos, yDPos, WIREWIDTH, abs(clicked2->y() - clicked1->y()));
//else
//w->setGeometry(xDPos, yDPos, 100, 100);
////w->setGeometry(xDPos, yDPos, abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), abs(clicked2->y() - clicked1->y()));
////temp->setText(QString::number(yPos));
//
//if (parentW->clickedWidget->x() != parentW->clickedWidget2->x()) {
//	//w->label->setGeometry(xPos + CONNECTORSIZE - 2, yPos + CONNECTORSIZE / 2 - 2, abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH);
//	QPoint lbl;
//	lbl = w->mapToGlobal(w->pos());
//	int parentx = w->x();
//	int parenty = w->y();
//	int x = w->mapToGlobal(w->pos()).x() + CONNECTORSIZE - 2 - xPos;
//	int y = w->mapToGlobal(w->pos()).y() + CONNECTORSIZE / 2 - 2 - yPos;
//	w->label->setGeometry(0, CONNECTORSIZE / 2 - 2 + BTNDELETESIZE, abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH);
//	//w->label->setGeometry(localW.x() - w->mapToGlobalx(), w->y(), abs(parentW->clickedWidget2->x() - parentW->clickedWidget->x()), WIREWIDTH);
//	w->label->setVisible(true);
//}
//if (parentW->clickedWidget->x() == parentW->clickedWidget2->x())
//w->label->setVisible(false);
//if (parentW->clickedWidget->y() != parentW->clickedWidget2->y()) {
//	//if click1 is above, norm length
//	//else, invert length
//	if (clicked1->y() < clicked2->y())
//		w->labelD->setGeometry(xDPos + CONNECTORSIZE - 2, yDPos + CONNECTORSIZE / 2 - 2, WIREWIDTH, -abs(clicked2->y() - clicked1->y()));
//	else
//		w->labelD->setGeometry(xDPos + CONNECTORSIZE - 2, yDPos + CONNECTORSIZE / 2 - 2, WIREWIDTH, abs(clicked2->y() - clicked1->y()));
//	w->labelD->setVisible(true);
//}
//
//w->btnDelete->setGeometry(w->width() - BTNDELETESIZE - 3, 0, BTNDELETESIZE - 3, BTNDELETESIZE);

//mouse move Connector
//temp->setText("pass");
	//WireWidget *w2 = new WireWidget(parentW); //need to change parent to board later on!!
	//w2->input->setVisible(false);
	//w2->input->setEnabled(false);
	//QPoint currPos = this->mapToGlobal(this->pos());
	//QPoint globalPos = event->globalPos(); //get mouse position
	//QPoint diff = globalPos - position;
	//QPoint newPosition = this->mapFromGlobal(currPos + diff);	
	//w2->setGeometry(this->x(), this->y(), newPosition.x() - this->x() - CONNECTORSIZE, WIREWIDTH);
	//w2->output->setGeometry(newPosition.x() - this->x(), this->y(), CONNECTORSIZE, CONNECTORSIZE );
	//position = globalPos;
	//w2->setVisible(true);