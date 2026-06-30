CREATE TABLE IF NOT EXISTS Users(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    category TEXT NOT NULL,
    role TEXT NOT NULL,
    ownerName TEXT,
    address TEXT,
    email TEXT,
    phone TEXT,
    licenseNumber TEXT,
    licenseExpiryDate TEXT,
    policyDetails TEXT,
    policyExpiryDate TEXT
);

CREATE TABLE IF NOT EXISTS MarketSchedule(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    foodCapacity INTEGER,
    artisanCapacity INTEGER
);

CREATE TABLE IF NOT EXISTS Waitlist(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vendorId INTEGER,
    weekId TEXT,
    category TEXT,
    FOREIGN KEY (vendorId) REFERENCES Users(id)
);

CREATE TABLE IF NOT EXISTS Bookings(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vendorId INTEGER,
    weekId TEXT,
    category TEXT,
    FOREIGN KEY (vendorId) REFERENCES Users(id),
    FOREIGN KEY (weekId) REFERENCES MarketSchedule(date)
);

-- The following Users in the market system
INSERT INTO Users (name, category, role, ownerName, address, email, phone, licenseNumber, licenseExpiryDate, policyDetails, policyExpiryDate) VALUES
    ('John Doe', 'Food', 'Vendor', 'John Doe', '123 Main St', 'john@example.com', '555-1234', 'F-123', '2027-01-01', 'FoodPolicyA', '2027-01-01'),
    ('Sue Smith', 'Food', 'Vendor', 'Sue Smith', '456 Oak Ave', 'sue@example.com', '555-5678', 'F-456', '2027-02-01', 'FoodPolicyB', '2027-02-01'),
    ('Joe Bloggs', 'Food', 'Vendor', 'Joe Bloggs', '789 Pine Rd', 'joe@example.com', '555-9012', 'F-789', '2027-03-01', 'FoodPolicyC', '2027-03-01'),
    ('Ruth Brown', 'Food', 'Vendor', 'Ruth Brown', '321 Maple St', 'ruth@example.com', '555-3456', 'F-321', '2027-04-01', 'FoodPolicyD', '2027-04-01'),
    ('Sally Johnson', 'Artisan', 'Vendor', 'Sally Johnson', '654 Cedar Ave', 'sally@example.com', '555-7890', 'A-654', '2027-05-01', 'ArtisanPolicyA', '2027-05-01'),
    ('Tom Brown', 'Artisan', 'Vendor', 'Tom Brown', '987 Spruce Rd', 'tom@example.com', '555-2345', 'A-987', '2027-06-01', 'ArtisanPolicyB', '2027-06-01'),
    ('Emily Davis', 'Artisan', 'Vendor', 'Emily Davis', '159 Elm St', 'emily@example.com', '555-6789', 'A-159', '2027-07-01', 'ArtisanPolicyC', '2027-07-01'),
    ('Michael Wilson', 'Artisan', 'Vendor', 'Michael Wilson', '753 Birch Rd', 'michael@example.com', '555-4321', 'A-753', '2027-08-01', 'ArtisanPolicyD', '2027-08-01'),
    ('Market Operator', 'Operator', 'Operator', 'Op Name', '1 Market St', 'operator@example.com', '555-0001', 'O-001', '2028-01-01', 'OpPolicy', '2028-01-01'),
    ('System Admin', 'Admin', 'Admin', 'Admin Name', '2 Admin Ave', 'admin@example.com', '555-0002', 'S-002', '2028-02-01', 'AdminPolicy', '2028-02-01');

--Market Schedule 
INSERT INTO MarketSchedule (date, foodCapacity, artisanCapacity) VALUES
    ('2026-03-01', 2, 2),
    ('2026-03-08', 2, 2),
    ('2026-03-15', 2, 2),
    ('2026-03-22', 2, 2);

-- The waitlist entries
INSERT INTO Waitlist (vendorId, weekId, category) VALUES
    (1, '2026-03-01', 'Food'),
    (2, '2026-03-01', 'Food'),
    (5, '2026-03-01', 'Artisan'),
    (6, '2026-03-01', 'Artisan');

-- the booking entries
INSERT INTO Bookings (vendorId, weekId, category) VALUES
    (3, '2026-03-08', 'Food'),
    (4, '2026-03-08', 'Food'),
    (7, '2026-03-08', 'Artisan'),
    (8, '2026-03-08', 'Artisan');