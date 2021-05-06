#include<QApplication>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsWidget>
#include<QStyleOption>
#include<Qpainter>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QState>
#include<QStateMachine>
#include<QtMath>
#include<QRandomGenerator>
#include<qpropertyanimation.h>
#include<qparallelanimationgroup.h>
#include<QSignalTransition>
#include<QTimer>

//自定义图像，方便进行动画设置
class Pixmap :public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
	Pixmap(const QPixmap& pix)
		:QObject(), QGraphicsPixmapItem(pix)
	{
		setCacheMode(QGraphicsPixmapItem::DeviceCoordinateCache);
	}
};
//自定义按钮，方便对按钮设置动画
class Button :public QGraphicsWidget
{
	Q_OBJECT
public:
	Button(const QPixmap &pixmap, QGraphicsItem*parent = nullptr)
		:QGraphicsWidget(parent), m_Pixmap(pixmap)
	{
		setAcceptHoverEvents(true);
		setCacheMode(QGraphicsItem::DeviceCoordinateCache);
	}
	QRectF boundingRect() const
	{
		return QRectF(-65, -65, 130, 130);
	}
	QPainterPath shape() const
	{
		QPainterPath path;
		path.addEllipse(boundingRect());
		return path;
	}
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
		QWidget* widget)
	{
		bool down = option->state & QStyle::State_Sunken;
		QRectF r = boundingRect();
		QLinearGradient grad(r.topLeft(), r.bottomRight());	//设置线性渐变
		grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
		grad.setColorAt(down ? 0 : 1, Qt::darkGray);
		painter->setPen(Qt::darkGray);
		painter->setBrush(grad);

		painter->drawEllipse(r);							//绘制一个圆形
		painter->drawEllipse(r.adjusted(5, 5, -5, -5));		//在上面的圆形之上画一个小一点的同心圆，让按钮看起来更有感觉

		painter->drawPixmap(-m_Pixmap.width() / 2, -m_Pixmap.height() / 2, m_Pixmap);	//把图片放在按钮上
	}
signals:
	void pressed();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent*)override
	{
		emit pressed();
		update();
	}
	void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override
	{
		update();
	}
private:
	QPixmap m_Pixmap;
};

class View :public QGraphicsView
{
public:
	View(QGraphicsScene* scene) :QGraphicsView(scene) {}
protected:
	void resizeEvent(QResizeEvent* ev)
	{
		QGraphicsView::resizeEvent(ev);
		//缩放视图矩阵和滚动滚动条，以确保场景矩形适合在视口中
		fitInView(sceneRect(), Qt::KeepAspectRatio);
	}
};

#include "main.moc"
int main(int argc,char *argv[])
{
	QApplication a(argc, argv);

	QPixmap kineticPix(":/images/kinetic.png");
	QPixmap bgPix(":/images/Time-For-Lunch-2.jpg");

	QGraphicsScene scene(-350,-350, 700, 700);	//让scene的原点保持在窗口中间

	//创建64个Pixmap图元，并保存到Qlist items
	QList<Pixmap*> items;
	for (int i = 0; i < 64; i++)
	{
		Pixmap* item = new Pixmap(kineticPix);
		item->setOffset(-kineticPix.width() / 2, -kineticPix.height() / 2);
		item->setZValue(i);
		items << item;		//把图元放进场景
		scene.addItem(item);
	}


	//创建五个按钮
	QGraphicsItem* btnParent = new QGraphicsRectItem;	//Item的坐标原点在中心
	Button* ellipseButton = new Button(QPixmap(":/images/ellipse.png"), btnParent);
	Button* figure8Button = new Button(QPixmap(":/images/figure8.png"), btnParent);
	Button* randomButton = new Button(QPixmap(":/images/random.png"), btnParent);
	Button* tiledButton = new Button(QPixmap(":/images/tile.png"), btnParent);
	Button* centeredButton = new Button(QPixmap(":/images/centered.png"), btnParent);

	//设置五个按钮的位置
	ellipseButton->setPos(-100, -100);
	figure8Button->setPos(100, -100);
	randomButton->setPos(0, 0);
	tiledButton->setPos(-100, 100);
	centeredButton->setPos(100, 100);

	scene.addItem(btnParent);			//把图元添加进场景
	btnParent->setTransform(QTransform::fromScale(0.75, 0.75));	//将btnParent进行缩放
	btnParent->setPos(200, 200);		//View的坐标原点也在中心
	btnParent->setZValue(65);			//设置堆叠顺序，数字大的在数字小的上面		


	//ui
	View* view = new View(&scene);
	view->setWindowTitle("Animated Tiles");
	//view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view->setBackgroundBrush(bgPix);					//设置背景画刷
	view->setCacheMode(QGraphicsView::CacheBackground);	//设置渲染缓冲，先在内存里面画好
	view->setRenderHints(QPainter::Antialiasing |		//抗锯齿和图形平滑
		QPainter::SmoothPixmapTransform);
	view->show();										//显示视图

	//状态机 可以从一种状态到另外一种状态改变
	/*
	组成
    一个最简单的状态机应该包括状态机（QStateMachine）、状态(QState)和过渡（QAbstractTransition子类)。状态机就相当于一个容器，过渡就是将某一个状态切换到另一个状态（当然也可以不切换）。
    使用
    1. 状态（QState）设置好此状态下的各对象的属性。
    2. 通过过渡指定它的目标状态。
    3. 将状态添加到状态机中。
    4. 状态机指定一个初始状态，然后调用start启动。
	*/

	//创建状态
	QState* rootState = new QState;
	QState* ellipseState = new QState(rootState);
	QState* figure8State = new QState(rootState);
	QState* randomState = new QState(rootState);
	QState* tiledState = new QState(rootState);
	QState* centeredState = new QState(rootState);

	//初始属性
	for (int i = 0; i < items.count(); i++)
	{
		Pixmap* item = items.at(i);
		//Ellipse
		ellipseState->assignProperty(item, "pos", QPointF(qCos((i / 63.0) * 6.28) * 250,
												  qSin((i / 63.0) * 6.28) * 250));
		
		// Figure 8
		figure8State->assignProperty(item, "pos",
			QPointF(qSin((i / 63.0) * 6.28) * 250,
				qSin(((i * 2) / 63.0) * 6.28) * 250));

		// Random
		randomState->assignProperty(item, "pos",
			QPointF(-250 + QRandomGenerator::global()->bounded(500),
				-250 + QRandomGenerator::global()->bounded(500)));

		// Tiled
		tiledState->assignProperty(item, "pos",
			QPointF(((i % 8) - 4) * kineticPix.width() + kineticPix.width() / 2,
				((i / 8) - 4) * kineticPix.height() + kineticPix.height() / 2));

		// Centered
		centeredState->assignProperty(item, "pos", QPointF());
	}

	//创建状态机，把上面的状态都存进去
	QStateMachine stateMachine;
	stateMachine.addState(rootState);
	stateMachine.setInitialState(rootState);	//设置初始状态
	rootState->setInitialState(centeredState);	//一开始让所有图片都在中间


	//创建动画
	QParallelAnimationGroup* group = new QParallelAnimationGroup;
	for (int i = 0; i < items.count(); i++)
	{
		QPropertyAnimation* animation = new QPropertyAnimation(items[i], "pos");
		animation->setDuration(750 + i * 25);
		animation->setEasingCurve(QEasingCurve::InOutBack);
		group->addAnimation(animation);
	}

	//给对象绑定指定信号产生，所切换到的状态
	auto trans = rootState->addTransition(ellipseButton, &Button::pressed, ellipseState);
	trans->addAnimation(group);	//把动画添加到过渡中

	trans = rootState->addTransition(figure8Button, &Button::pressed, figure8State);
	trans->addAnimation(group);

	trans = rootState->addTransition(randomButton, &Button::pressed, randomState);
	trans->addAnimation(group);

	trans = rootState->addTransition(tiledButton, &Button::pressed, tiledState);
	trans->addAnimation(group);

	trans = rootState->addTransition(centeredButton, &Button::pressed, centeredState);
	trans->addAnimation(group);

	//打开程序的时候来一个默认动画
	QTimer timer;
	timer.start(125);
	timer.setSingleShot(true);	//只触发一次
	trans = rootState->addTransition(&timer, &QTimer::timeout, ellipseState);
	trans->addAnimation(group);


	stateMachine.start();


	return a.exec();
}