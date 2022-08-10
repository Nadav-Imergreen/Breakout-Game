#include "Board.h"

Board::Board()
{
	init();		//initilise paddle and ball posotion & size

	//initilise 3 sides frames

	m_frames.push_back(std::make_unique<Frame>(RIGHT_FRAME_POSITION, RIGHT_FRAME_SIZE, FRAME_P::RIGHT_P));
	m_frames.push_back(std::make_unique<Frame>(LEFT_FRAME_POSITION, LEFT_FRAME_SIZE, FRAME_P::LEFT_P));
	m_frames.push_back(std::make_unique<Frame>(TOP_FRAME_POSITION, TOP_FRAME_SIZE, FRAME_P::UP_P));
}

void Board::draw(sf::RenderWindow& window)
{
	for (auto& frame : m_frames)
		frame->drawRect(window);

	for (auto& gift : m_gifts)
		gift->drawSprite(window);

	for (auto& brick : m_bricks)
		brick->drawSprite(window);
		

	m_paddle->drawSprite(window);
	m_ball->drawSprite(window);

	m_info.draw(window);
}

void Board::setPaddleDirection(sf::Vector2f dir)
{
	m_paddle->setDirection(dir);
}

void Board::setBallAngle()
{
	m_ball->setAngle();
}

bool Board::update(const sf::Time& delta)
{
	//move objects
	
	move(*m_paddle, delta);
	move(*m_ball, delta);

	for (auto& gift : m_gifts)
	{
		if (gift->isBrickBroke())
			gift->fall(delta);
	}

	//check - delete brick
	std::erase_if(m_bricks, [](auto& unmovable)
		{
			return unmovable->haveToDelete();
		});

	//check - delete gift
	std::erase_if(m_gifts, [](auto& unmovable)
		{
			return unmovable->haveToDelete();
		});

	//check - if player took add score gift
	if (m_paddle->addScore())
	{
		m_info.addScore();
		m_paddle->setGifts2false();
	}

	//check - if player took add life gift
	if (m_paddle->addLife())
	{
		m_info.addLife();
		m_paddle->setGifts2false();
	}

	//check - if player took strong ball gift
	if (m_paddle->isStrongBall())
		m_ball->setStrongBall(true);
	else
		m_ball->setStrongBall(false);


	//check - if player hits all the bricks - win level
	if (m_bricks.size() == 0)
		return true;

	return false;
}

void Board::loadLevel(const LevelMap& map, const sf::Vector2i& size)
{
	int randomGift; // to randomlly peek type of gift

	//when start the level - clear structurs and initilise objects
	m_bricks.clear();
	m_gifts.clear();
	init();
	
	sf::Vector2f objSize;
	objSize.x = (WIN_W - 10) / size.x; 
	objSize.y =  30;

	for (size_t row = 0; row < size.x; row++)
	{
		for (size_t col = 0; col < size.y; col++)
		{
			sf::Vector2f objPosition(objSize.x / 2 + 5 + col * objSize.x, INFO_H + 5 + objSize.y / 2 + row * objSize.y);
			switch (map[row][col])
			{
			case STRONG_BRICK:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::StrongBrick), DOUBLE_HIT));
				break;

			case ORANGE:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::Orange), SINGLE_HIT));
				break;

			case RED:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::Red), SINGLE_HIT));
				break;

			case PURPLE:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::Purple), SINGLE_HIT));
				break;

			case YELLOW:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::Yellow), SINGLE_HIT));
				break;

			case GREEN:
				m_bricks.push_back(std::make_unique<Brick>(objPosition, objSize, &Resources::instance().getTexture(TextureType::Green), SINGLE_HIT));
				break;

			case GIFT_BRICK:
				m_bricks.push_back(std::make_unique<GiftBrick>(objPosition, objSize));

			    randomGift = rand() % NUM_OF_GIFTS;     //random chossed type of gift
					switch (randomGift)
					{
					case RESIZE_PADDLE:
						m_gifts.push_back(std::make_unique<ResizePaddleGift>(objPosition, objSize));
						break;

					case CHANGE_DIR:
						m_gifts.push_back(std::make_unique<ChangeDirGift>(objPosition, objSize));
						break;

					case FAST_PADDLE:
						m_gifts.push_back(std::make_unique<FastPaddleGift>(objPosition, objSize));
						break;

					case STRONG_BALL:
						m_gifts.push_back(std::make_unique<StrongBallGift>(objPosition, objSize));
						break;

					case ADD_SCORE:
						m_gifts.push_back(std::make_unique<AddScoreGift>(objPosition, objSize));
						break;

					case ADD_LIFE:
						m_gifts.push_back(std::make_unique<AddLifeGift>(objPosition, objSize));
						break;

					default:
						break;
					}
				break;

			default:
				break;
			}
		}
	}
}

void Board::nextLevel()
{
	m_info.nextLevel();
}

const LevelSituation& Board::levelLost()
{
	if (m_ball->getPosition().y >= WIN_H && m_info.getLives() == 1)
		return LevelSituation::LostGame;

	else if (m_ball->getPosition().y >= WIN_H && m_info.getLives() > 1)
	{
		m_info.updateLives();
		return LevelSituation::LostLife;
	}
}



void Board::move(MovingObject& obj, const sf::Time& delta)
{
	// move object
	obj.move(delta);

	//check collision beteen 2 object and handle accordingly

	if(obj.collideWith(*m_paddle))
		obj.handleCollision(*m_paddle);

	if (obj.collideWith(*m_ball))
		obj.handleCollision(*m_ball);

	for (auto& frame : m_frames)
		if (obj.collideWithRect(*frame))
			obj.handleCollision(*frame);

	for (auto& gift : m_gifts)
		if (obj.collideWith(*gift))
			obj.handleCollision(*gift);

	for (auto& brick : m_bricks)
		if (obj.collideWith(*brick))
		{
			if (typeid(*brick) == typeid(GiftBrick))	//check if the hited brick have a gift inside
			{
				for (auto& gift : m_gifts)
				{
					if (brick->getPosition() == gift->getPosition())	//find which gift is free now and make it fall-down
						gift->setGiftBrickHit();
				}
			}
			obj.handleCollision(*brick);
			m_info.updateScore();	//add score when hit a brick
		}		
}

void Board::init()
{
	//initilise paddle and ball posotion & size

	m_paddle = (std::make_unique<Paddle>(PADDLE_POSITION, PADDLE_SIZE));
	m_ball = (std::make_unique<Ball>(BALL_POSITION, BALL_SIZE));
}

void Board::restartInfo()
{
	m_info.restart();
}

bool Board::isPause() const
{
	return m_info.isPause();
}

void Board::handleClick(sf::RenderWindow& window, sf::Vector2f location)
{
	m_info.handleClick(window, location);
}

void Board::handleMouseMoved(sf::RenderWindow& window, sf::Vector2f location)
{
	m_info.handleMouseMoved(window, location);
}

int Board::getScore() const
{
	return m_info.getScore();
}
