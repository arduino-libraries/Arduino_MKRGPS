# Arduino MKR GPS library

## Methods

### `begin()`

Initialize the GPS.

#### Syntax 

```
GPS.begin()
GPS.begin(mode)
```

#### Parameters

`GPS_MODE_I2C` to use the MKR GPS with the I2C cable (default setting), `GPS_MODE_SHIELD` if using the MKR GPS as a shield.

#### Returns

1 on success, 0 on failure.

#### Example

```
if (!GPS.begin()) {
    Serial.println("Failed to initialize the GPS!");
    while(1);
}
```

#### See also

* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `end()`

De-initialize the GPS.

#### Syntax 

```
GPS.end()
```

#### Parameters

None.

#### Returns

Nothing.

#### Example

```
if (!GPS.begin()) {
    Serial.println("Failed to initialize the GPS!");
    while(1);
}

// Read GPS data here...

// Done working with the GPS
GPS.end();
```

#### See also

* [begin()](#begin)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `available()`

Query if new GPS data is available().

#### Syntax 

```
GPS.available()
```

#### Parameters

None.

#### Returns

0 if no new GPS data is available, 1 if new GPS data is available.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float latitude = GPS.latitude();
    float longitude = GPS.longitude();
    float altitude = GPS.altitude();
    float speed = GPS.speed();
    int satellites = GPS.satellites();

    // ...
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `latitude()`

Read the latitude of the GPS.

#### Syntax 

```
GPS.latitude()
```

#### Parameters

None.

#### Returns

GPS latitude in degrees.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float latitude = GPS.latitude();
    float longitude = GPS.longitude();

    // ...

    // Print GPS data
    Serial.print("Location: ");
    Serial.print(latitude, 7);
    Serial.print(", ");
    Serial.println(longitude, 7);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `longitude()`

Read the latitude of the GPS.

#### Syntax 

```
GPS.latitude()
```

#### Parameters

None.

#### Returns

GPS longitude in degrees.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float latitude = GPS.latitude();
    float longitude = GPS.longitude();

    // ...

    // Print GPS data
    Serial.print("Location: ");
    Serial.print(latitude, 7);
    Serial.print(", ");
    Serial.println(longitude, 7);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `speed()`

Read the ground speed of the GPS.

#### Syntax 

```
GPS.speed()
```

#### Parameters

None.

#### Returns

GPS ground speed in km/h. 

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float speed = GPS.speed();

    // ...

    // Print GPS data
    Serial.print("Ground speed: ");
    Serial.print(speed);
    Serial.println(" km/h");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `course()`

Read the course of the GPS.

#### Syntax 

```
GPS.course()
```

#### Parameters

None.

#### Returns

GPS course in degrees. 

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float course = GPS.course();

    // ...

    // Print GPS data
    Serial.print("Course: ");
    Serial.print(course);
    Serial.println(" degrees");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `variation()`

Read the magnetic variation of the GPS.

#### Syntax 

```
GPS.variation()
```

#### Parameters

None.

#### Returns

GPS magnetic variation in degrees.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float variation = GPS.variation();

    // ...

    // Print GPS data
    Serial.print("Variation: ");
    Serial.print(variation);
    Serial.println(" degrees");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `altitude()`

Read the altitude of the GPS.

#### Syntax 

```
GPS.altitude()
```

#### Parameters

None.

#### Returns

GPS altitude in meters. 

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS data
    float altitude = GPS.altitude();

    // ...

    // Print GPS data
    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println("m");
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `satellites()`

Read the number of satellites being tracked by the GPS.

#### Syntax 

```
GPS.satellites()
```

#### Parameters

None.

#### Returns

The number of satellites being tracked by the GPS.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS values
    int satellites = GPS.satellites();

    // ...

    // Print GPS data
    Serial.print("Number of satellites: ");
    Serial.println(satellites);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `satellites()`

Read the number of satellites being tracked by the GPS.

#### Syntax 

```
GPS.satellites()
```

#### Parameters

None.

#### Returns

The number of satellites being tracked by the GPS.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS values
    int satellites = GPS.satellites();

    // ...

    // Print GPS data
    Serial.print("Number of satellites: ");
    Serial.println(satellites);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [getTime()](#gettime)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `getTime()`

Read the current epoch time from the GPS.

#### Syntax 

```
GPS.getTime()
```

#### Parameters

None.

#### Returns

The current epoch time from the GPS.

#### Example

```
// Check if there is new GPS data available
if (GPS.available()) {
    // Read GPS values
    unsigned long epochTime = GPS.getTime();

    // ...

    // Print GPS data
    Serial.print("Epoch time: ");
    Serial.println(epochTime);
}
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [standby()](#standby)
* [wakeup()](#wakeup)

### `standby()`

Put the GPS in standby mode.

#### Syntax 

```
GPS.standby()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
// Put the GPS in standby mode
Serial.println("Standby mode");
GPS.standby();

// Wait for 10 seconds
delay(10000);

// Wake up the GPS
Serial.println("Wakeup");
GPS.wakeup();

// Wait for new GPS data to become available
Serial.print("Waiting new location data... ");
while (!GPS.available());

// ...
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [wakeup()](#wakeup)

### `wakeup()`

Wake up the GPS from standby mode.

#### Syntax 

```
GPS.wakeup()
```

#### Parameters

None.

#### Returns

None.

#### Example

```
// Put the GPS in standby mode
Serial.println("Standby mode");
GPS.standby();

// Wait for 10 seconds
delay(10000);

// Wake up the GPS
Serial.println("Wakeup");
GPS.wakeup();

// Wait for new GPS data to become available
Serial.print("Waiting new location data... ");
while (!GPS.available());

// ...
```

#### See also

* [begin()](#begin)
* [end()](#end)
* [available()](#available)
* [latitude()](#latitude)
* [longitude()](#longitude)
* [speed()](#speed)
* [course()](#course)
* [variation()](#variation)
* [altitude()](#altitude)
* [satellites()](#satellites)
* [getTime()](#gettime)
* [standby()](#standby)