#!/bin/bash
# Combines multiple github size permitted files to create Ratings.csv

gunzip RatingsFile/*

cat RatingsFile/RatingsFileaa > Ratings.csv
cat RatingsFile/RatingsFileab >> Ratings.csv
cat RatingsFile/RatingsFileac >> Ratings.csv
cat RatingsFile/RatingsFilead >> Ratings.csv
cat RatingsFile/RatingsFileae >> Ratings.csv
cat RatingsFile/RatingsFileaf >> Ratings.csv

