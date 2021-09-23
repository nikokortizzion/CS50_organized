SELECT title FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON stars.person_id = people.id
WHERE
name = "Johnny Depp"
AND
movie_id IN (
SELECT movie_id FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE
name = "Helena Bonham Carter"
);
