import * as THREE from 'three';

export interface AsciiOptions {
  charSize?: number;
}

export class DynamicAsciiEffect {
  private renderer: THREE.WebGLRenderer;
  private renderTarget: THREE.WebGLRenderTarget;
  private quadScene: THREE.Scene;
  private quadCamera: THREE.OrthographicCamera;
  private material: THREE.ShaderMaterial;

  constructor(renderer: THREE.WebGLRenderer, charSet = ' .:-=+*#%@', options: AsciiOptions = {}) {
    this.renderer = renderer;

    const width = window.innerWidth;
    const height = window.innerHeight;
    
    this.renderTarget = new THREE.WebGLRenderTarget(width, height, {
      minFilter: THREE.LinearFilter,
      magFilter: THREE.LinearFilter,
      format: THREE.RGBAFormat,
    });

    const tAscii = this.createAsciiTexture(charSet);

    const vertexShader = `
      varying vec2 vUv;
      void main() {
        vUv = uv;
        gl_Position = vec4(position, 1.0);
      }
    `;

    const fragmentShader = `
      uniform sampler2D tDiffuse;
      uniform sampler2D tAscii;
      uniform vec2 resolution;
      uniform float charCount;
      uniform vec2 charSize;

      varying vec2 vUv;

      void main() {
        vec2 cellCount = resolution / charSize;
        vec2 gridUv = floor(vUv * cellCount) / cellCount;
        vec2 centerUv = gridUv + (0.5 / cellCount);
        
        vec4 color = texture2D(tDiffuse, centerUv);
        
        float luma = dot(color.rgb, vec3(0.299, 0.587, 0.114));
        float brightness = smoothstep(0.05, 0.85, luma);
        
        float charIdx = floor(brightness * (charCount - 0.001));
        
        vec2 localUv = fract(vUv * cellCount);
        vec2 atlasUv = vec2((charIdx + localUv.x) / charCount, localUv.y);
        
        vec4 asciiShape = texture2D(tAscii, atlasUv);
        
        vec3 finalColor = color.rgb * asciiShape.r;
        gl_FragColor = vec4(finalColor, 1.0);
      }
    `;

    const cSize = options.charSize ?? 6;

    this.material = new THREE.ShaderMaterial({
      uniforms: {
        tDiffuse: { value: this.renderTarget.texture },
        tAscii: { value: tAscii },
        resolution: { value: new THREE.Vector2(width, height) },
        charCount: { value: charSet.length },
        charSize: { value: new THREE.Vector2(cSize, cSize * 2) },
      },
      vertexShader,
      fragmentShader,
    });

    this.quadScene = new THREE.Scene();
    this.quadCamera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0, 1);
    const quadGeometry = new THREE.PlaneGeometry(2, 2);
    const quadMesh = new THREE.Mesh(quadGeometry, this.material);
    this.quadScene.add(quadMesh);
  }

  private createAsciiTexture(charSet: string): THREE.CanvasTexture {
    const charCount = charSet.length;
    const charWidth = 32;
    const charHeight = 64;
    
    const canvas = document.createElement('canvas');
    canvas.width = charWidth * charCount;
    canvas.height = charHeight;
    
    const ctx = canvas.getContext('2d');
    if (ctx) {
      ctx.fillStyle = '#000000';
      ctx.fillRect(0, 0, canvas.width, canvas.height);
      ctx.fillStyle = '#ffffff';
      ctx.font = 'bold 48px monospace';
      ctx.textAlign = 'center';
      ctx.textBaseline = 'middle';
      for (let i = 0; i < charCount; i++) {
        ctx.fillText(charSet[i], i * charWidth + charWidth / 2, charHeight / 2);
      }
    }
    
    const texture = new THREE.CanvasTexture(canvas);
    texture.minFilter = THREE.LinearFilter;
    texture.magFilter = THREE.LinearFilter;
    return texture;
  }

  setSize(w: number, h: number): void {
    this.renderTarget.setSize(w, h);
    this.material.uniforms.resolution.value.set(w, h);
  }

  render(scene: THREE.Scene, camera: THREE.Camera): void {
    this.renderer.setRenderTarget(this.renderTarget);
    this.renderer.render(scene, camera);
    
    this.renderer.setRenderTarget(null);
    this.renderer.render(this.quadScene, this.quadCamera);
  }
}