-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get crime description
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- Get interviews transcript
SELECT transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Get list of cars license plate and names of owners wich they belong that left parking lot within ten minutes of theft
SELECT courthouse_security_logs.license_plate, name FROM courthouse_security_logs
JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- 5P2BI95 | Patrick
-- 94KL13X | Ernest
-- 6P58WS2 | Amber
-- 4328GD8 | Danielle
-- G412CB7 | Roger
-- L93JTIZ | Elizabeth
-- 322W7JE | Russell
-- 0NTHK55 | Evelyn

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Get list of account_numbers and names of owners that withdraw money at ATM on Fifer Street
SELECT bank_accounts.account_number, name from bank_accounts
JOIN people ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";
-- 49610011 | Ernest
-- 26013199 | Russell
-- 16153065 | Roy
-- 28296815 | Bobby
-- 25506511 | Elizabeth
-- 28500762 | Danielle
-- 76054385 | Madison
-- 81061156 | Victoria

-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Get list of callers and their names which has duration of conversation less then 1 minute
SELECT caller, name FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
-- (130) 555-0289 | Roger
-- (499) 555-9472 | Evelyn
-- (367) 555-5533 | Ernest
-- (609) 555-5876 | Kathryn
-- (499) 555-9472 | Evelyn
-- (286) 555-6063 | Madison
-- (770) 555-1861 | Russell
-- (031) 555-6622 | Kimberly
-- (826) 555-1652 | Bobby
-- (338) 555-6650 | Victoria
-- Get list receivers whom call people listed before
SELECT receiver, name FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
-- (996) 555-8899 | Jack
-- (892) 555-8872 | Larry
-- (375) 555-8161 | Berthold
-- (389) 555-5198 | Danielle
-- (717) 555-1342 | Melissa
-- (676) 555-6554 | James
-- (725) 555-3243 | Philip
-- (910) 555-3251 | Jacqueline
-- (066) 555-9701 | Doris
-- (704) 555-2131 | Anna

-- Get list of names of cities and time of flight out from Fiftyville on next day
SELECT city, hour, minute FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
WHERE year = 2020 AND month = 7 AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour;
-- London        | 8  | 20
-- Chicago       | 9  | 30
-- San Francisco | 12 | 15
-- Tokyo         | 15 | 20
-- Boston        | 16 | 0

-- Get list of passengers of earliest flight
SELECT name FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
AND destination_airport_id = (SELECT id FROM airports WHERE city = 'London'));
-- Roger
-- Ernest
-- Edward
-- Evelyn
-- Madison
-- Bobby
-- Danielle

-- Get name of suspect who in lists that was got earlier
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs
        WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25)
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60)
AND passport_number IN (SELECT passport_number FROM passengers
    WHERE flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29
    AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
    AND destination_airport_id = (SELECT id FROM airports WHERE city = 'London')))
AND id IN (SELECT person_id FROM bank_accounts
    WHERE account_number IN (SELECT account_number FROM atm_transactions
    WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- Ernest

-- Get name of accomplice whom supect called during leaving crime scene
SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60
    AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));
-- Berthold
