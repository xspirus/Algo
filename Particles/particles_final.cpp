#include <iostream>
#include <vector>
#include <algorithm>

#define BSIZE 1<<15
#define LIMIT 0.0001

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

//________________________________________________________________________//

/*** Particle Class ***/

/**
 *  The particles class. It contains the velocity, the start time
 *  and if destrction has been brought upon each particle that will
 *  be fired from the cannons.
 */
class Particle {

private:

    int velocity, start, destroyed;

public:

    void put(int velocity, int start);
    double distance(double t);
    double end(int len);
    bool isDestroyed();
    bool skip(double t);
    void destroy();

};

/**
 *  Puts velocity and start time read.
 *  destroyed is 0 because in the beginning everything is intact.
 *  @param velocity The velocity.
 *  @param startTime The start time.
 */
void Particle::put(int velocity, int start)  {

    this->velocity = velocity;
    this->start = start;
    this->destroyed = 0;

}

/**
 *  Calculates the distance travelled so far in time t.
 *  @param t The current time stamp.
 *  @return distance travelled.
 */
double Particle::distance(double t) {

    return (velocity * (t - start));

}

/**
 *  Calculates when the particle will reach the other end.
 *  @param len The length to travel.
 *  @return time to travel to other end.
 */
double Particle::end(int len) {

    return (1.0 * len / velocity + start);

}

/**
 *  Find if object is destroyed.
 *  @return true iff destroyed is 1.
 */
bool Particle::isDestroyed() {

    return (destroyed == 1);

}

/**
 *  Find if from this particle and on
 *  all remaining particles have not
 *  been fired yet.
 *  @param t The current timestamp.
 *  @result true iff particle not fired yet.
 */
bool Particle::skip(double t) {

    return (t < (double)start);

}

/**
 *  Set particle as destroyed.
 */
void Particle::destroy() {

    this->destroyed = 1;

}

//________________________________________________________________________//

/**
 *  The EndPair Class. Contains for each particle (with index)
 *  the time it needs to reach the other end.
 */
class EndPair {

public:

    int index;
    double endTime;

    void put(int index, double endTime);

    /**
     *  Used in sort of algorithm.
     */
    bool operator < (const EndPair &other) const {

        return (endTime < other.endTime);

    }

};

/**
 *  Initialise index and endTime.
 */
void EndPair::put(int index, double endTime) {

    this->index = index;
    this->endTime = endTime;

}

//________________________________________________________________________//

/*** Pair Class ***/

/*
 *  A simple integer pair class.
 */
class Pair {

public:

    int left, right;

};

//________________________________________________________________________//

/*** Functions Declaration ***/

int read_int();
double min(vector<EndPair> &le, vector<Particle> &lp, int &li, vector<EndPair> &re, vector<Particle> &rp, int &ri);

void find_collision(int size, int len, double &timeLeft, double &timeRight, vector<Particle> &left, vector<Particle> &right);

void read_particles(int cannons, vector<Particle> &particles);
void find_ends(int cannons, int length, vector<Particle> &particles, vector<EndPair> &ends);

//________________________________________________________________________//

/*** Main ***/

int main() {

    int cannons, length, collisions;
    int i;
    int li, ri;
    double timeLeft, timeRight;

    cannons = read_int();
    length = read_int();
    collisions = read_int();

    vector<Particle> left(cannons);
    vector<EndPair> endLeft(cannons);
    vector<Particle> right(cannons);
    vector<EndPair> endRight(cannons);

    read_particles(cannons, left);
    read_particles(cannons, right);

    find_ends(cannons, length, left, endLeft);
    find_ends(cannons, length, right, endRight);

    sort(endLeft.begin(), endLeft.end());
    sort(endRight.begin(), endRight.end());

    vector<Pair> collision(collisions);

    timeLeft = 0;
    li = 0;
    ri = 0;
    for (i = 0; i < collisions; i++) {

        timeRight = min(endLeft, left, li, endRight, right, ri);
        find_collision(cannons, length, timeLeft, timeRight, left, right);

    }

    return 0;

}

//________________________________________________________________________//

/*** Functions Code ***/

int read_int() {

    int d = 0, x = 0;
    char c;

    while (1)  {

        if (bpos >= bsize) {

            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);

        }

        c = buffer[bpos++];
        if (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
            return x;

    }

    return -1;

}

/**
 *  A function to find the minimum endTime of the next
 *  not destroyed Particle. Overtakes destroyed particles
 *  and compares the two active minimum particle endTimes.
 *  @param le The endTimes for left
 *  @param lp The left particles
 *  @param li The left index
 *  @param re The endTimes for right
 *  @param rp The right particles
 *  @param ri The right index
 *  @return the minimum endTime
 */
double min(vector<EndPair> &le, vector<Particle> &lp, int &li, vector<EndPair> &re, vector<Particle> &rp, int &ri) {

    while (lp[le[li].index].isDestroyed())
        li++;

    while (rp[re[ri].index].isDestroyed())
        ri++;

    if (le[li] < re[ri])
        return le[li++].endTime;

    return re[ri++].endTime;

}

/*
 *  A function to read the velocities and start times of
 *  the particles for each cannon.
 *  @param cannons The number of particles to be shot.
 *  @param particles The vector containing the cannons particle specs.
 */
void read_particles(int cannons, vector<Particle> &particles) {

    int i, t, v;

    for (i = 0; i < cannons; i++) {

        t = read_int();
        v = read_int();
        particles[i].put(v, t);

    }

}

/*
 *  A function to find, for each particle, the time to reach the other end.
 *  @param cannons The number of particles to be shot.
 *  @param length The distance to be travelled.
 *  @param particles The particles with velocities and start times.
 *  @param ends The int vector with endTimes;
 */
void find_ends(int cannons, int length, vector<Particle> &particles, vector<EndPair> &ends) {

    int i;

    for (i = 0; i < cannons; i++)
        ends[i].put(i, particles[i].end(length));

}

/**
 *  The fuction which implements the algorithm to find the collisions.
 *  Before calling the fuction we have found the min endTime which will
 *  be the right edge for our binary search in time. We know that for each
 *  particle before it reaches the end it will find another particle of the
 *  other side. So if e.g. particle1right needs 10 secs to reach the other
 *  side, then we are certain that within that time some collision
 *  is going to happen (not for particle1right necessarily). At first call the
 *  left edge is 0 and after that the timestamp of the previous collision.
 *  We set a limit for the accuracy of the time of the collision to 0.0001.
 *  So as long as the two edges have a difference of over 0.0001 we continue
 *  searching. Every time we search we go to mid time (between the two edges).
 *  We calculate the max distance a left particle has travelled and we check if
 *  it has passed any of the right particles. If yes the mid becomes right edge
 *  (found collision ==> need to go earlier in time to find when it happened).
 *  If not the mid becomes left edge (no collision ==> need to go later in time
 *  to find the collision that will happen). After we reach the limit we know
 *  the collision will happen in the right edge. In that time we find the left
 *  max and the right that it will collide with.
 */
void find_collision(int size, int len, double &timeLeft, double &timeRight, vector<Particle> &left, vector<Particle> &right) {

    int i;
    double mid;
    int count;
    double max, temp;
    int rLeft = 0, rRight = 0;

    while ((timeRight - timeLeft) > LIMIT) {

        max = 0;
        count = 0;
        mid = (timeLeft + timeRight) / 2;

        for (i = 0; i < size; i++) {

            // Don't calculate destroyed particles.
            if (left[i].isDestroyed())
                continue;

            // Skip all next not fired particles.
            if (left[i].skip(mid))
                break;

            temp = left[i].distance(mid);

            if (temp > max)
                max = temp;

        }

        for (i = 0; i < size; i++) {

            // Don't calculate destroyed particles.
            if (right[i].isDestroyed())
                continue;

            // Skip all next not fired particles.
            if (right[i].skip(mid))
                break;

            temp = right[i].distance(mid);

            if (max + temp >= len) {

                count++;
                break;

            }

        }

        // No collision.
        if (count == 0)
            timeLeft = mid;
        // Collision.
        else
            timeRight = mid;
    }

    max = 0;

    for (i = 0; i < size; i++) {

        // Don't calculate destroyed particles.
        if (left[i].isDestroyed())
            continue;

        // Skip all next not fired particles.
        if (left[i].skip(timeRight))
            break;

        temp = left[i].distance(timeRight);

        if (temp > max) {

            max = temp;
            rLeft = i;

        }

    }

    for (i = 0; i < size; i++) {

        // Don't calculate destroyed particles.
        if (right[i].isDestroyed())
            continue;

        // Skip all next not fired particles.
        if (right[i].skip(timeRight))
            break;

        temp = right[i].distance(timeRight);

        if (max + temp >= len) {

            rRight = i;
            break;

        }

    }

    timeLeft = timeRight;
    left[rLeft].destroy();
    right[rRight].destroy();
    printf("%d %d\n", (rLeft + 1), (rRight + 1));

    return;

}
