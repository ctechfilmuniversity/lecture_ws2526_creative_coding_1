let angle = 0;
let shapes = [];
let ringRadius = 150;

function setup() {
  createCanvas(1550, 750, WEBGL);
  generateScene();
}

function generateScene() {
  for (let i = 0; i < 50; i++) {
    shapes.push({
      x: random(-400, 400),
      y: random(-400, 400),
      zOffset: random(TWO_PI),
      x_small: random(-100,100),
      y_small: random(-100,100),
     r: random(200, 255),
g: random(80, 220),
b: random(0, 40),
r_p:random(230,250),
g_p:random(60,160),
b_p:random(110,150),
      radius: random(20, 40)
    });
  }
}

function draw() {
  background(10, 20, 50);

  ambientLight(150);
  directionalLight(255, 255, 255, 0, 0, -1);

  orbitControl();

  angle += 0.01;

  for (let s of shapes) {
    push();

    let z = sin(angle + s.zOffset) * ringRadius;

        translate(s.x_small, s.y_small, z);
        fill(s.r_p, s.g_p, s.b_p);

    noStroke();
    sphere(s.radius, 20, 20);

        translate(s.x, s.y, z);
    fill(s.r, s.g, s.b);
    noStroke();
    sphere(s.radius, 20, 20);
    pop();
  }
}
