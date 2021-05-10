#include<QApplication>
#include<QGraphicsObject>
#include<QGraphicsView>
#include<QPixmap>
#include<QPainter>
#include<QToolBar>
#include<QTextEdit>
#include<QPushButton>
#include<QRadioButton>
#include<QGraphicsProxyWidget>
#include<QGroupBox>
#include<QVBoxLayout>

class Pixmap : public QGraphicsObject
{
	Q_OBJECT
public:
	Pixmap(const QPixmap& pix)
		:QGraphicsObject(), m_pix(pix)
	{

	}
	QRectF boundingRect() const
	{
		return m_pix.rect();
	}
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		//让图片贴到中间
		painter->drawPixmap(QPoint(0,0), m_pix);
	}

private:
	QPixmap m_pix;
};
#include "main_states.moc"	//和当前cpp文件名要一致
class GraphicsView :public QGraphicsView
{
public:
	GraphicsView(QGraphicsScene* scene) :QGraphicsView(scene)
	{
	}
	void resizeEvent(QResizeEvent* ev)
	{
		//View大小发送变化的时候，让场景保持宽度比例
		fitInView(sceneRect(), Qt::KeepAspectRatio);
	}
};

int main(int argc,char *argv[])
{
	QApplication a(argc, argv);

	// Text edit and button
	QTextEdit* edit = new QTextEdit(
		"My name is maye,Welcome to follow \
		my WeChat public account <C语言Plus>");
	QPushButton* btn = new QPushButton;
	QGraphicsProxyWidget* btnProxy = new QGraphicsProxyWidget;
	btnProxy->setWidget(btn);	//把按钮嵌入代理窗口
	auto editProxy = new QGraphicsProxyWidget;
	editProxy->setWidget(edit);

	//创建一个组合框，并设置垂直布局，同时添加三个单选按钮
	auto* box = new QGroupBox;
	box->setFlat(true);
	box->setTitle("Options");

	auto* vLayout = new QVBoxLayout;
	box->setLayout(vLayout);
	vLayout->addWidget(new QRadioButton("Herring"));
	vLayout->addWidget(new QRadioButton("Blue Parrot"));
	vLayout->addWidget(new QRadioButton("Petunias"));

	auto* boxProxy = new QGraphicsProxyWidget;
	boxProxy->setWidget(box);







	QGraphicsScene* scene = new QGraphicsScene;
	scene->addItem(boxProxy);
	


	GraphicsView view(scene);
	edit->setParent(&view);

	view.show();

	return a.exec();
}
