#include "FDPixelSprite.h"
#include "FontChina.h"

FDPixelSprite::FDPixelSprite()
{

}
FDPixelSprite::~FDPixelSprite()
{

}

FDPixelSprite* FDPixelSprite::create(String Url)
{
	FDPixelSprite *sprite = new FDPixelSprite();
	if (sprite && sprite->initWithFile(Url.getCString())) {
		sprite->setName(Url.getCString());
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	sprite = NULL;


	return NULL;
}


void FDPixelSprite::setimg(String Url) {
	img = new Image();
	img->initWithImageFile(FileUtils::getInstance()->fullPathForFilename(Url.getCString()).c_str());

}



void FDPixelSprite::onEnter()
{
	Sprite::onEnter();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->onTouchBegan = CC_CALLBACK_2(FDPixelSprite::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
}


void FDPixelSprite::onExit()
{
	Sprite::onExit();
	_eventDispatcher->removeEventListener(m_listener);
}

bool FDPixelSprite::onTouchBegan(/*String thismapurl, */Touch *pTouch, Event *pEvent)
{
	if (this->isContainTouchLocation(pTouch)) {
		Color4B c = { 0, 0, 0, 0 };

		Size winSize = Director::getInstance()->getWinSize();

		Point touchPoint = pTouch->getLocationInView();

		Size cSize = this->getContentSize();
		Point point = this->getAnchorPointInPoints();
		point = ccp(cSize.width - point.x, cSize.height - point.y);
		Point pos(this->getPositionX() - point.x, winSize.height - this->getPositionY() - point.y);

		Point localPoint = ccp(touchPoint.x - pos.x,
			touchPoint.y - pos.y);

		float scaleFactor = Director::getInstance()->getContentScaleFactor();
		unsigned int x = localPoint.x  * scaleFactor, y = localPoint.y * scaleFactor;

		float _width = this->getContentSize().width*scaleFactor;

		//This method is currently only supports symmetric image
		//unsigned char *data_ = this->getTexture()->getFDImageData();

		//Efficiency of this method is relatively low
		//CCImage * img = new CCImage();
		//img->initWithImageFileThreadSafe(CCFileUtils::sharedFileUtils()->fullPathForFilename(thismapurl.getCString()).c_str());
		unsigned char *data_ = img->getData();


		unsigned int *pixel = (unsigned int *)data_;
		pixel = pixel + (y * (int)_width) * 1 + x * 1;

		c.r = *pixel & 0xff;
		c.g = (*pixel >> 8) & 0xff;
		c.b = (*pixel >> 16) & 0xff;
		c.a = (*pixel >> 24) & 0xff;
		if (c.a == 0) {
			//log(FontChina::G2U("不可点击！"));
			return false;
		}
		else
		{
			//log(FontChina::G2U("可点击！"));
			return true;
		}
	}
	return false;
}


Rect FDPixelSprite::atlasRect()
{
	Size cSize = this->getContentSize();
	Point point = this->getAnchorPointInPoints();
	return Rect(-point.x, -point.y, cSize.width, cSize.height);
}


bool FDPixelSprite::isContainTouchLocation(Touch *pTouch)
{
	return this->atlasRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}
