#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Tile.h"
#include "SolveResult.h"

typedef unsigned int row;
typedef unsigned int column;
typedef unsigned int square;
typedef unsigned int tile_index;

class Board
{
public:
	Board();
	~Board();

	bool load(const std::string &path);
	SolveResult solve();
	const bool isSolveable() const;
	void print() const;

	inline const row getRow(const unsigned int &index, const unsigned int &width) const;
	inline const column getColumn(const unsigned int &index, const unsigned int &width) const;
	inline const square getTileSquare(const tile_index &index) const;
	inline const square getTileSquare(const column &c, const row &r) const;
	inline const unsigned int translate(const column &c, const row &r, const unsigned int &width) const;

private:
	const unsigned int SIZE = 9;
	const unsigned int SQUARE_SIZE = 3;
	std::vector<Tile> _tiles;
	
	SolveResult backtrack(tile_index index, SolveResult &result);

	inline const bool isTileInsertionValid(const tile_index &index) const;
	inline const bool isRowInsertionValid(const tile_index& index) const;
	inline const bool isColumnInsertionValid(const tile_index& index) const;
	inline const bool isSquareInsertionValid(const tile_index& index) const;
};