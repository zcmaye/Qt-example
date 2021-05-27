#include "buttontester.h"
#include<QDebug>
ButtonTester::ButtonTester(QWidget *parent)
	: QTextEdit(parent)
{
	this->setMouseTracking(true);
}

ButtonTester::~ButtonTester()
{
}
void ButtonTester::whatBtn(QMouseEvent *ev)
{
    int number = ButtonTester::buttonByNumber(ev->button());
    qDebug() << QString::number(number);
    QString result = "Mouse Press:raw button=" + QString::number(number)
        + " Qt=" + ButtonTester::enumNameFromValue(ev->button());
    QString btnString = ButtonTester::enumNamesFromMouseButtons(ev->buttons());
    result += "\nheldbuttons->" + btnString;
    this->setText(result);
}
void ButtonTester::mousePressEvent(QMouseEvent* ev)
{
    whatBtn(ev);
}

void ButtonTester::mouseMoveEvent(QMouseEvent* ev)
{
    whatBtn(ev);
}

void ButtonTester::mouseReleaseEvent(QMouseEvent* ev)
{
    whatBtn(ev);
}

void ButtonTester::wheelEvent(QWheelEvent* ev)
{
    QString result;
    QPoint numDegrees = ev->angleDelta() / 8;
    if (numDegrees.x() > 0)
    {
        result = "Mouse Wheel Event:LEFT";
    }
    else if(numDegrees.x()<0)
    {
        result = "Mouse Wheel Event:RIGHT";
    }

    if (numDegrees.y() > 0)
    {
        result = "Mouse Wheel Event:UP";
    }
    else if (numDegrees.y() < 0)
    {
        result = "Mouse Wheel Event:DOWN";
    }
    this->setText(result);
   

    qDebug() << ev->angleDelta()<<"  " << numDegrees;

    ev->accept();

}

int ButtonTester::buttonByNumber(const Qt::MouseButton btn)
{
	switch (btn)
	{
	case Qt::NoButton:		return 0;
		//鼠标基本功能键
	case Qt::LeftButton:	return 1;
	case Qt::RightButton:	return 2;
	case Qt::MidButton:		return 3;
		//鼠标的其他功能键
	case Qt::BackButton:	return 8;
	case Qt::ForwardButton:	return 9;
	case Qt::TaskButton:	return 10;
	case Qt::ExtraButton4:	return 11;
	case Qt::ExtraButton5:	return 12;
	case Qt::ExtraButton6:	return 13;
	case Qt::ExtraButton7:	return 14;
	case Qt::ExtraButton8:	return 15;
	case Qt::ExtraButton9:	return 16;
	case Qt::ExtraButton10:	return 17;
	case Qt::ExtraButton11:	return 18;
	case Qt::ExtraButton12:	return 19;
	case Qt::ExtraButton13:	return 20;
	case Qt::ExtraButton14:	return 21;
	case Qt::ExtraButton15:	return 22;
	case Qt::ExtraButton16:	return 23;
	case Qt::ExtraButton17:	return 24;
	case Qt::ExtraButton18:	return 25;
	case Qt::ExtraButton19:	return 26;
	case Qt::ExtraButton20:	return 27;
	case Qt::ExtraButton21:	return 28;
	case Qt::ExtraButton22:	return 29;
	case Qt::ExtraButton23:	return 30;
	case Qt::ExtraButton24:	return 31;
	}
	return 0;
}
QString ButtonTester::enumNameFromValue(const Qt::MouseButton button)
{
    if (button == Qt::NoButton)      return "NoButton";
    if (button == Qt::LeftButton)    return "LeftButton";
    if (button == Qt::RightButton)   return "RightButton";
    if (button == Qt::MiddleButton)  return "MiddleButton";
    if (button == Qt::BackButton)    return "BackButton";
    if (button == Qt::ForwardButton) return "ForwardButton";
    if (button == Qt::TaskButton)    return "TaskButton";
    if (button == Qt::ExtraButton4)  return "ExtraButton4";
    if (button == Qt::ExtraButton5)  return "ExtraButton5";
    if (button == Qt::ExtraButton6)  return "ExtraButton6";
    if (button == Qt::ExtraButton7)  return "ExtraButton7";
    if (button == Qt::ExtraButton8)  return "ExtraButton8";
    if (button == Qt::ExtraButton9)  return "ExtraButton9";
    if (button == Qt::ExtraButton10) return "ExtraButton10";
    if (button == Qt::ExtraButton11) return "ExtraButton11";
    if (button == Qt::ExtraButton12) return "ExtraButton12";
    if (button == Qt::ExtraButton13) return "ExtraButton13";
    if (button == Qt::ExtraButton14) return "ExtraButton14";
    if (button == Qt::ExtraButton15) return "ExtraButton15";
    if (button == Qt::ExtraButton16) return "ExtraButton16";
    if (button == Qt::ExtraButton17) return "ExtraButton17";
    if (button == Qt::ExtraButton18) return "ExtraButton18";
    if (button == Qt::ExtraButton19) return "ExtraButton19";
    if (button == Qt::ExtraButton20) return "ExtraButton20";
    if (button == Qt::ExtraButton21) return "ExtraButton21";
    if (button == Qt::ExtraButton22) return "ExtraButton22";
    if (button == Qt::ExtraButton23) return "ExtraButton23";
    if (button == Qt::ExtraButton24) return "ExtraButton24";
    qDebug("QMouseShortcutEntry::addShortcut contained Invalid Qt::MouseButton value");
    return "NoButton";
}

QString ButtonTester::enumNamesFromMouseButtons(const Qt::MouseButtons buttons)
{
    QString returnText = "";
    if (buttons == Qt::NoButton)      return "NoButton";
    if (buttons & Qt::LeftButton)    returnText += "LeftButton ";
    if (buttons & Qt::RightButton)   returnText += "RightButton ";
    if (buttons & Qt::MiddleButton)  returnText += "MiddleButton ";
    if (buttons & Qt::BackButton)    returnText += "BackButton ";
    if (buttons & Qt::ForwardButton) returnText += "ForwardButton ";
    if (buttons & Qt::TaskButton)    returnText += "TaskButton ";
    if (buttons & Qt::ExtraButton4)  returnText += "ExtraButton4 ";
    if (buttons & Qt::ExtraButton5)  returnText += "ExtraButton5 ";
    if (buttons & Qt::ExtraButton6)  returnText += "ExtraButton6 ";
    if (buttons & Qt::ExtraButton7)  returnText += "ExtraButton7 ";
    if (buttons & Qt::ExtraButton8)  returnText += "ExtraButton8 ";
    if (buttons & Qt::ExtraButton9)  returnText += "ExtraButton9 ";
    if (buttons & Qt::ExtraButton10) returnText += "ExtraButton10 ";
    if (buttons & Qt::ExtraButton11) returnText += "ExtraButton11 ";
    if (buttons & Qt::ExtraButton12) returnText += "ExtraButton12 ";
    if (buttons & Qt::ExtraButton13) returnText += "ExtraButton13 ";
    if (buttons & Qt::ExtraButton14) returnText += "ExtraButton14 ";
    if (buttons & Qt::ExtraButton15) returnText += "ExtraButton15 ";
    if (buttons & Qt::ExtraButton16) returnText += "ExtraButton16 ";
    if (buttons & Qt::ExtraButton17) returnText += "ExtraButton17 ";
    if (buttons & Qt::ExtraButton18) returnText += "ExtraButton18 ";
    if (buttons & Qt::ExtraButton19) returnText += "ExtraButton19 ";
    if (buttons & Qt::ExtraButton20) returnText += "ExtraButton20 ";
    if (buttons & Qt::ExtraButton21) returnText += "ExtraButton21 ";
    if (buttons & Qt::ExtraButton22) returnText += "ExtraButton22 ";
    if (buttons & Qt::ExtraButton23) returnText += "ExtraButton23 ";
    if (buttons & Qt::ExtraButton24) returnText += "ExtraButton24 ";
    return returnText;
}
