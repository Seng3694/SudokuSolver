#include "Board.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>

Board::Board()
{
	_tiles.resize(81);
}

Board::~Board()
{
	_tiles.clear();
}

bool Board::load(const std::string &path)
{
	std::ifstream stream(path);
	std::string buffer;

	if (!stream)
		return false;

	stream.seekg(0, std::ios::end);
	buffer.resize(stream.tellg());
	stream.seekg(0);
	stream.read(&buffer[0], buffer.size());
	stream.close();

	std::regex nonNumeric("[^0-9]");

	buffer = std::regex_replace(buffer, nonNumeric, "");

	if (buffer.size() != 81)
		return false;

	std::vector<Tile> tiles;

	for (auto &c : buffer)
	{
		auto t = Tile{};
		t.value = (TileValue)(c - '0');

		if (t.value == TileValue::Empty)
			t.status = TileStatus::Empty;
		else
			t.status = TileStatus::Solved;

		tiles.push_back(t);
	}

	_tiles = tiles;
	return true;
}

const bool Board::isSolveable() const
{
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		if (_tiles[i].status != TileStatus::Empty && !isTileInsertionValid(i))
			return false;
	}

	return true;
}

SolveResult Board::solve()
{
	auto result = SolveResult{};
	if (isSolveable())
		return backtrack(0, result);
	else
		return result;
}

SolveResult Board::backtrack(tile_index index, SolveResult &result)
{
	if (index == _tiles.size())
	{
		result.solved = true;
		return result;
	}

	if (_tiles[index].status != TileStatus::Solved)
	{
		for (unsigned int i = 0; i < Board::SIZE; ++i)
		{
			_tiles[index].value = (TileValue)(i + 1);
			_tiles[index].status = TileStatus::Processing;

			if (isTileInsertionValid(index))
			{
				auto r = backtrack(index + 1, result);
				if (r.solved)
					return r;
			}
		}

		_tiles[index].value = TileValue::Empty;
		_tiles[index].status = TileStatus::Empty;
	}
	else
	{
		auto r = backtrack(index + 1, result);
		if (r.solved)
			return r;
	}

	++result.backtracks;
	result.solved = false;
	return result;
}

inline const bool Board::isTileInsertionValid(const tile_index &index) const
{
	return isRowInsertionValid(index)
		&& isColumnInsertionValid(index)
		&& isSquareInsertionValid(index);
}

inline const bool Board::isRowInsertionValid(const tile_index& index) const
{
	auto tile = _tiles[index];
	auto tileRow = getRow(index, Board::SIZE);
	auto tileColumn = getColumn(index, Board::SIZE);

	for (column c = 0; c < Board::SIZE; ++c)
	{
		if (c != tileColumn)
		{
			auto i = translate(c, tileRow, Board::SIZE);
			if (_tiles[i].value == tile.value)
				return false;
		}
	}

	return true;
}

inline const bool Board::isColumnInsertionValid(const tile_index& index) const
{
	auto tile = _tiles[index];
	auto tileRow = getRow(index, Board::SIZE);
	auto tileColumn = getColumn(index, Board::SIZE);

	for (row r = 0; r < Board::SIZE; ++r)
	{
		if (r != tileRow)
		{
			auto i = translate(tileColumn, r, Board::SIZE);
			if (_tiles[i].value == tile.value)
				return false;
		}
	}

	return true;
}

inline const bool Board::isSquareInsertionValid(const tile_index& index) const
{
	auto tile = _tiles[index];
	auto squareIndex = getTileSquare(index);
	auto squareColumn = getColumn(squareIndex, Board::SQUARE_SIZE);
	auto squareRow = getRow(squareIndex, Board::SQUARE_SIZE);

	auto minColumn = squareColumn * Board::SQUARE_SIZE;
	auto maxColumn = (squareColumn + 1) * Board::SQUARE_SIZE - 1;
	auto minRow = squareRow * Board::SQUARE_SIZE;
	auto maxRow = (squareRow + 1) * Board::SQUARE_SIZE - 1;

	for (row r = minRow; r <= maxRow; ++r)
	{
		for (column c = minColumn; c <= maxColumn; ++c)
		{
			auto i = translate(c, r, Board::SIZE);
			if (i != index && _tiles[i].value == tile.value)
				return false;
		}
	}

	return true;
}

void Board::print() const
{
	for (row r = 0; r < Board::SIZE; r++)
	{
		std::cout << std::endl;

		for (column c = 0; c < Board::SIZE; c++)
		{
			auto tile = _tiles[translate(c, r, Board::SIZE)];
			auto value = tile.value == TileValue::Empty ? '-' : static_cast<char>((int)tile.value + 48);

			std::cout << "  " << value << " ";

			if ((c + 1) % Board::SQUARE_SIZE == 0 && c != Board::SIZE - 1)
				std::cout << "|";
		}

		std::cout << std::endl;

		if ((r + 1) % Board::SQUARE_SIZE == 0 && r != Board::SIZE - 1)
		{
			std::cout << std::string(38, '_') << std::endl;
		}
	}

}

inline const unsigned int Board::translate(const column &c, const row &r, const unsigned int &width) const
{
	return r * width + c;
}

inline const row Board::getRow(const unsigned &index, const unsigned int &width) const
{
	return index / width;
}

inline const column Board::getColumn(const unsigned int &index, const unsigned int &width) const
{
	return index % width;
}

inline const square Board::getTileSquare(const column &c, const row &r) const
{
	auto squareRow = r / SQUARE_SIZE;
	auto squareColumn = c / SQUARE_SIZE;

	return translate(squareColumn, squareRow, SQUARE_SIZE);
}

inline const square Board::getTileSquare(const tile_index &index) const
{
	auto row = getRow(index, Board::SIZE);
	auto column = getColumn(index, Board::SIZE);

	return getTileSquare(column, row);
}
