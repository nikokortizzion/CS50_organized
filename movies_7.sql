SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
AND NOT rating IS NULL
ORDER BY rating DESC, title ASC;
