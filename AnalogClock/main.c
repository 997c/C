#include <SFML/Graphics.h>
#include <math.h>
#include <time.h>

typedef struct {
    sfRectangleShape* shape;
    float length;
    float thickness;
} ClockHand;

typedef struct {
    sfVector2f position;
    float radius;
    sfCircleShape* face;
    sfCircleShape* center;
    ClockHand hourHand;
    ClockHand minuteHand;
    ClockHand secondHand;
    sfRectangleShape** hourMarks;
    int hourMarksCount;
    sfRectangleShape** minuteMarks;
    int minuteMarksCount;
} AnalogClock;

ClockHand createClockHand(float length, float thickness, sfColor color) {
    ClockHand hand;
    hand.shape = sfRectangleShape_create();
    hand.length = length;
    hand.thickness = thickness;
    
    sfRectangleShape_setSize(hand.shape, (sfVector2f){thickness, length});
    sfRectangleShape_setFillColor(hand.shape, color);
    sfRectangleShape_setOrigin(hand.shape, (sfVector2f){thickness / 2.0f, length});
    
    return hand;
}

void setClockHandRotation(ClockHand* hand, float angle) {
    sfRectangleShape_setRotation(hand->shape, angle);
}

void setClockHandPosition(ClockHand* hand, sfVector2f position) {
    sfRectangleShape_setPosition(hand->shape, position);
}

AnalogClock createAnalogClock(float radius, sfVector2f position) {
    AnalogClock clock;
    clock.position = position;
    clock.radius = radius;
    
    // Create clock face
    clock.face = sfCircleShape_create();
    sfCircleShape_setRadius(clock.face, radius);
    sfCircleShape_setFillColor(clock.face, sfColor_fromRGB(240, 240, 240));
    sfCircleShape_setOutlineThickness(clock.face, radius * 0.02f);
    sfCircleShape_setOutlineColor(clock.face, sfBlack);
    sfCircleShape_setOrigin(clock.face, (sfVector2f){radius, radius});
    sfCircleShape_setPosition(clock.face, position);
    
    // Create center
    clock.center = sfCircleShape_create();
    sfCircleShape_setRadius(clock.center, radius * 0.03f);
    sfCircleShape_setFillColor(clock.center, sfBlack);
    sfCircleShape_setOrigin(clock.center, (sfVector2f){clock.radius * 0.03f, clock.radius * 0.03f});
    sfCircleShape_setPosition(clock.center, position);
    
    // Create clock hands
    clock.hourHand = createClockHand(radius * 0.5f, radius * 0.03f, sfBlack);
    clock.minuteHand = createClockHand(radius * 0.8f, radius * 0.02f, sfBlack);
    clock.secondHand = createClockHand(radius * 0.9f, radius * 0.01f, sfRed);
    
    setClockHandPosition(&clock.hourHand, position);
    setClockHandPosition(&clock.minuteHand, position);
    setClockHandPosition(&clock.secondHand, position);
    
    // Create hour marks
    clock.hourMarksCount = 12;
    clock.hourMarks = malloc(clock.hourMarksCount * sizeof(sfRectangleShape*));
    
    for (int i = 0; i < 12; ++i) {
        clock.hourMarks[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(clock.hourMarks[i], (sfVector2f){radius * 0.02f, radius * 0.1f});
        sfRectangleShape_setFillColor(clock.hourMarks[i], sfBlack);
        
        float angle = i * 30.0f;
        float x = radius * 0.85f * sinf(angle * 3.14159265f / 180.0f);
        float y = -radius * 0.85f * cosf(angle * 3.14159265f / 180.0f);
        
        sfRectangleShape_setPosition(clock.hourMarks[i], (sfVector2f){position.x + x, position.y + y});
        sfRectangleShape_setRotation(clock.hourMarks[i], angle);
    }
    
    // Create minute marks
    clock.minuteMarksCount = 48; // 60 minutes minus 12 hour marks
    clock.minuteMarks = malloc(clock.minuteMarksCount * sizeof(sfRectangleShape*));
    
    int markIndex = 0;
    for (int i = 0; i < 60; ++i) {
        if (i % 5 == 0) continue; // Skip positions where hour marks are
        
        clock.minuteMarks[markIndex] = sfRectangleShape_create();
        sfRectangleShape_setSize(clock.minuteMarks[markIndex], (sfVector2f){radius * 0.01f, radius * 0.05f});
        sfRectangleShape_setFillColor(clock.minuteMarks[markIndex], sfBlack);
        
        float angle = i * 6.0f;
        float x = radius * 0.9f * sinf(angle * 3.14159265f / 180.0f);
        float y = -radius * 0.9f * cosf(angle * 3.14159265f / 180.0f);
        
        sfRectangleShape_setPosition(clock.minuteMarks[markIndex], (sfVector2f){position.x + x, position.y + y});
        sfRectangleShape_setRotation(clock.minuteMarks[markIndex], angle);
        
        markIndex++;
    }
    
    return clock;
}

void updateAnalogClock(AnalogClock* clock) {
    // Get current time
    time_t now = time(NULL);
    struct tm* localTime = localtime(&now);
    
    // Calculate angles
    float hourAngle = (localTime->tm_hour % 12) * 30.0f + localTime->tm_min * 0.5f;
    float minuteAngle = localTime->tm_min * 6.0f;
    float secondAngle = localTime->tm_sec * 6.0f;
    
    // Set rotations
    setClockHandRotation(&clock->hourHand, hourAngle);
    setClockHandRotation(&clock->minuteHand, minuteAngle);
    setClockHandRotation(&clock->secondHand, secondAngle);
}

void drawAnalogClock(const AnalogClock* clock, sfRenderWindow* window) {
    sfRenderWindow_drawCircleShape(window, clock->face, NULL);
    
    for (int i = 0; i < clock->hourMarksCount; ++i) {
        sfRenderWindow_drawRectangleShape(window, clock->hourMarks[i], NULL);
    }
    
    for (int i = 0; i < clock->minuteMarksCount; ++i) {
        sfRenderWindow_drawRectangleShape(window, clock->minuteMarks[i], NULL);
    }
    
    sfRenderWindow_drawRectangleShape(window, clock->hourHand.shape, NULL);
    sfRenderWindow_drawRectangleShape(window, clock->minuteHand.shape, NULL);
    sfRenderWindow_drawRectangleShape(window, clock->secondHand.shape, NULL);
    sfRenderWindow_drawCircleShape(window, clock->center, NULL);
}

void setAnalogClockPosition(AnalogClock* clock, sfVector2f position) {
    clock->position = position;
    sfCircleShape_setPosition(clock->face, position);
    sfCircleShape_setPosition(clock->center, position);
    
    setClockHandPosition(&clock->hourHand, position);
    setClockHandPosition(&clock->minuteHand, position);
    setClockHandPosition(&clock->secondHand, position);
    
    // Update marks positions
    for (int i = 0; i < clock->hourMarksCount; ++i) {
        sfFloatRect bounds = sfRectangleShape_getLocalBounds(clock->hourMarks[i]);
        sfRectangleShape_setOrigin(clock->hourMarks[i], (sfVector2f){bounds.width / 2, bounds.height / 2});
        sfRectangleShape_setPosition(clock->hourMarks[i], position);
    }
    
    for (int i = 0; i < clock->minuteMarksCount; ++i) {
        sfFloatRect bounds = sfRectangleShape_getLocalBounds(clock->minuteMarks[i]);
        sfRectangleShape_setOrigin(clock->minuteMarks[i], (sfVector2f){bounds.width / 2, bounds.height / 2});
        sfRectangleShape_setPosition(clock->minuteMarks[i], position);
    }
}

void destroyAnalogClock(AnalogClock* clock) {
    sfCircleShape_destroy(clock->face);
    sfCircleShape_destroy(clock->center);
    
    sfRectangleShape_destroy(clock->hourHand.shape);
    sfRectangleShape_destroy(clock->minuteHand.shape);
    sfRectangleShape_destroy(clock->secondHand.shape);
    
    for (int i = 0; i < clock->hourMarksCount; ++i) {
        sfRectangleShape_destroy(clock->hourMarks[i]);
    }
    free(clock->hourMarks);
    
    for (int i = 0; i < clock->minuteMarksCount; ++i) {
        sfRectangleShape_destroy(clock->minuteMarks[i]);
    }
    free(clock->minuteMarks);
}

int main() {
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    
    sfRenderWindow* window = sfRenderWindow_create(
        (sfVideoMode){windowWidth, windowHeight, 32},
        "Analog Clock",
        sfClose,
        NULL
    );
    sfRenderWindow_setFramerateLimit(window, 60);
    
    // Create clock centered in the window
    float clockRadius = (windowWidth < windowHeight ? windowWidth : windowHeight) * 0.4f;
    AnalogClock clock = createAnalogClock(
        clockRadius,
        (sfVector2f){windowWidth / 2.0f, windowHeight / 2.0f}
    );
    
    // Main loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }
        
        // Update clock
        updateAnalogClock(&clock);
        
        // Draw
        sfRenderWindow_clear(window, sfWhite);
        drawAnalogClock(&clock, window);
        sfRenderWindow_display(window);
    }
    
    // Cleanup
    destroyAnalogClock(&clock);
    sfRenderWindow_destroy(window);
    
    return 0;
}