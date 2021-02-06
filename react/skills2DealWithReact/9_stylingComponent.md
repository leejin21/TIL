# 9.1 가장 흔한 방식, 일반 CSS

컴포넌트를 스타일링하는 가장 기본적인 방식.

✨ **CSS 클래스를 중복되지 않게 만드는 것이 가장 중요** ✨

## 방법1. 이름 지을 때 특별 규칙 사용

-   컴포넌트이름-클래스이름 형태
    ex) App-header
-   BEM naming
    ex) .card\_\_title-primary

## 방법2. CSS selector

-   예제 코드(App.css)

    ```css
    .App {
        text-align: center;
    }
    /* .App 안에 들어 있는 .logo */
    .App .logo {
        animation: App-logo-spin infinite 20s linear;
        height: 40vmin;
        pointer-events: none;
    }

    /* .App 안에 들어 있는 header
    	header 클래스가 아닌 header 태그 자체에 
    	스타일을 적용하기 때문에 .이 생략됨
    */
    .App header {
        background-color: #282c34;
        min-height: 100vh;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        font-size: calc(10px+2vmin);
        color: white;
    }

    .App a {
        color: #61dafb;
    }

    @keyframes App-logo-spin {
        from {
            transform: rotate(0deg);
        }
        to {
            transform: rotate(360deg);
        }
    }
    ```

keyframes
: 개발자가 애니메이션의 중간중간 처리를 할 수 있도록 하는@규칙(at-rule).

-   예제 코드(App.js)

    ```powershell
    import React, { Component } from 'react';

    class App extends Component {
    	render() {
    		return (
    			<div className="App">
    				<header>
    					<img src={logo} className="logo" alt="logo"/>
    					<p>Edit <code>src/App.js</code> and save to reload.</p>
    					<a
    						href="https://reactjs.org"
    						target="_blank"
    						rel="noopener noreferrer"
    						>
    							Learn React
    					</a>
    				</header>
    			</div>
    		);
    	}
    }

    export default App;
    ```

# 9.2 Sass 사용하기

자주 사용되는 CSS 전처리기 중 하나. 확장된 CSS 문법을 사용하여 CSS 코드를 더욱 쉽게 작성할 수 있도록 해 줌.

## node-sass 설치

```powershell
npm install --save node-sass
# 1번 명령어
npm install --save node-sass@4.14.1
# 2번 명령어
```

1번 명령어로 설치하면 다음과 같은 에러가 뜨기 때문에 2번 명령어로 설치하기.

Error: Node Sass version 5.0.0 is incompatible with ^4.0.0

## utils 함수 분리

-   예제 코드(utils.scss)
-   예제 코드(SassComponent.scss)

## sass-loader 설정 커스터마이징하기

하지만 새 파일 생성할 때마다 `@import './utils.scss'`를 매번 추가하는 게 귀찮을 수도 있음.

⇒ 설정 커스텀하면 해결

```powershell
git add .
git commit -m "commit before npm eject"
npm eject
```

이후 `config/webpack.config.js` 에서 sassRegex로 찾은 후(ctrl+ f ) 아래 코드와 같이 .concat부터로 수정

-   코드(config/webpack.config.js)

    ```jsx
    						{
                  test: sassRegex,
                  exclude: sassModuleRegex,
                  use: getStyleLoaders(
                    {
                      importLoaders: 3,
                      sourceMap: isEnvProduction
                        ? shouldUseSourceMap
                        : isEnvDevelopment,
                    },
                    'sass-loader'
                  ).concat({
                    loader: require.resolve('sass-loader'),
                    options: {
                      sassOptions: {
                        includePaths: [paths.appSrc, '/styles'],
                      },
                      sourceMap: isEnvProduction && shouldUseSourceMap,
                      prependData: `@import 'utils';`
                    }
                  }),
                  // Don't consider CSS imports dead code even if the
                  // containing package claims to have no side effects.
                  // Remove this when webpack adds a warning or an error for this.
                  // See https://github.com/webpack/webpack/issues/6571
                  sideEffects: true,
                },
                // Adds support for CSS Modules, but using SASS
                // using the extension .module.scss or .module.sass
                {
                  test: sassModuleRegex,
                  use: getStyleLoaders(
                    {
                      importLoaders: 3,
                      sourceMap: isEnvProduction
                        ? shouldUseSourceMap
                        : isEnvDevelopment,
                      modules: {
                        getLocalIdent: getCSSModuleLocalIdent,
                      },
                    },
                    'sass-loader'
                  ),
                },
    ```

-   예제 코드(SassComponent.scss)

    ```scss
    @import "utils.scss";
    .SassComponent {
        display: flex;
        .box {
            // 일반 CSS에서는 .SassComponent .box와 마찬가지
            background: red;
            cursor: pointer;
            transition: all 0.3s ease-in;

            &.red {
                background: $red;
                @include square(1);
            }
            &.orange {
                background: $orange;
                @include square(2);
            }
            &.yellow {
                background: $yellow;
                @include square(3);
            }
            &.green {
                background: $green;
                @include square(4);
            }
            &.blue {
                background: $blue;
                @include square(5);
            }
            &.indigo {
                background: $indigo;
                @include square(6);
            }
            &.violet {
                background: $violet;
                @include square(7);
            }
            &.hover {
                background: black;
            }
        }
    }
    ```

## node modules에서 라이브러리 불러오기

```scss
@import "~open-color/open-color";
@import "~include-media/dist/include-media";
```

# 9.3 CSS 모듈

CSS 모듈: 스타일을 작성할 때 CSS 클래스가 다른 CSS 클래스의 이름과 충돌하지 않도록 파일마다 고유한 이름([파일이름]_[클래스이름]_[해시값])을 _자동으로 생성해 줌._

➕ .module.css 확장자로 파일을 저장하기만 하면 CSS Module이 적용됨.

-   예제 코드(CSSModule.module.css)

    ```scss
    // 자동으로 고유해짐: 흔히 사용되는 단어를 클래스 이름으로 마음대로 사용 가능.
    .wrapper {
        background: black;
        padding: 1em;
        color: white;
        font-size: 2rem;
    }
    // 글로벌 CSS로 사용하고 싶으면
    :gloval .something {
        font-weight: 800;
        color: aqua;
    }
    ```

-   예제 코드(CSSModule.js)

    ```jsx
    import React from "react";
    import styles from "./CSSModule.module.css";

    const CSSModule = () => {
        return (
            <div className={styles.wrapper}>
                안녕하세요, 저는
                <span className="something"> 리액트입니다.</span>
            </div>
        );
    };

    export default CSSModule;
    ```

장점: CSS 모듈을 사용하면 클래스 이름을 지을 때 그 고유성에 대해 고민하지 않아도 됨.

## 클래스 이름을 2개 이상 적용하고 싶을 때

### 방법 1. template literal

-   예제 코드

    ```jsx
    // ES6 template literal
    <div className={`${styles.wrapper} ${styles.inverted}`}>
        안녕하세요, 저는
        <span className="something"> 리액트입니다.</span>
    </div>
    ```

### 방법 2. join

-   예제 코드

    ```jsx
    classNames={[styles.inverted, styles.wrapper].join('')}
    ```

## classnames

CSS 클래스를 조건부로 설정할 때 유용한 라이브러리(여러 클래스 적용할 때 편리).

-   예시 코드

    ```jsx
    const MyComponent = ({ highlighted, theme }) => {
        return (
            <div className={classNames("MyComponent", { highlighted }, theme)}>
                Hello
            </div>
        );
    };
    ```

이떄 highlighted가

-   `true`인 경우: highlighted 클래스 적용
-   `false`인 경우: highlighted 적용 X
-   예시 코드(CSSModule.js)

## Sass와 함께 사용하기

Sass를 사용할 때도 `[파일이름].module.scss`와 같은 형태로 파일명을 지어주면 CSS module로 사용 가능.

-   예제 코드(CSSModule.module.scss)

    똑같이 작동됨.

    ```jsx
    .wrapper {
        background: black;
        padding: 1em;
        color: white;
        font-size: 2rem;
        &.inverted {
            // inverted가 .wrapper와 함께 사용되었을 때만 적용
            background: white;
            color: black;
            border: 1px solid black;
        }
    }
    /* 글로벌 CSS를 작성하고 싶다면 */
    :global {
        .something {
            font-weight: 800;
            color: aqua;
        }
    }
    ```

# 9.4 styled-components

`CSS-in-JS`: 스타일을 js 파일에 내장시키는 방식.

스타일을 작성하는 것과 동시에 해당 스타일이 적용된 컴포넌트를 만들 수 있게 해 줌.

```powershell
npm install styled-components
# VS code에서 extension 설치: vscode-styled-components
```

-   예제 코드(StyledComponent.js)

    ```jsx
    import React from "react";
    import styled, { css } from "styled-components";

    const Box = styled.div`
        /* props로 넣어준 값을 직접 전달해 줄 수 있음 */
        background: ${(props) => props.color || "blue"};
        padding: 1rem;
        display: flex;
    `;

    const Button = styled.button`
        background: white;
        color: black;
        border-radius: 4px;
        padding: 0.5rem;
        display: flex;
        align-items: center;
        justify-content: center;
        box-sizing: border-box;
        font-size: 1rem;
        font-weight: 600;
        /* & 문자를 사용하여 Sass처럼 자기 자신 선택 가능 */
        &:hover {
            background: rgba(255, 255, 255, 0.9);
        }

        /* 다음 코드는 inverted 값이 true일 때 특정 스타일을 부여해 줌 */
        ${(props) =>
            props.inverted &&
            css`
                background: none;
                border: 2px solid white;
                color: white;
                &:hover {
                    background: white;
                    color: black;
                }
            `};
        & + button {
            margin-left: 1rem;
        }
    `;

    const StyledComponents = () => (
        <Box color="black">
            <Button>안녕하세요</Button>
            <Button inverted={true}>테두리만</Button>
        </Box>
    );

    export default StyledComponents;
    ```

## Tagged 템플릿 리터럴

템플릿에 객체를 넣거나 함수를 넣으면 형태를 잃어 버림(예: `() ⇒ 'world!'` 같은 함수도 그대로 문자열화됨)

→ BUT Tagged 템플릿 리터럴을 사용하면 템플릿 사이사이에 들어가는 js 객체나 함수의 원본 값을 그대로 추출할 수 있음. styled-components는 이런 속성을 사용해 styled-components로 만든 컴포넌트의 props를 스타일 쪽에서 쉽게 조회할 수 있게 함.

## 스타일링된 element 만들기

styled-components를 사용해 스타일링된 element를 만들 때는 컴포넌트 파일의 상단에서 styled를 불러오고, styled.태그명을 사용해 구현함.

```jsx
import styled from "style-components";

const MyComponent = styled.div`
    font-size: 2rem;
`;
```

⇒ styled.div 뒤에 Tagged 템플릿 리터럴 문법을 통해 스타일을 넣어 주면, 해당 스타일이 적용된 div로 이루어진 리액트 컴포넌트가 생성됨.

### 태그명이 유동적인 경우 or 특정 컴포넌트 자체에 스타일링

-   코드

    ```jsx
    // 태그의 타입을 styled 함수의 인자로 전달
    const MyInput = styled("input")`
        background: gray;
    `;
    // 아예 컴포넌트 형식의 값을 넣어 줌.
    const StyledLink = styled(Link)`
        color: blue;
    `;
    // Link: 나중에 리액트 라우터를 배울 때 사용할 컴포넌트.
    // 해당 컴포넌트에서 className props를 최상위 DOM의 className 값으로 설정해야 함.
    const Link = ({ className }) => {
        return <div className={className}>Sample</div>;
    };
    ```

## 스타일에서 props 조회하기

-   이전에 작성했던 Box Component

    ```jsx
    const Box = styled.div`
    	/*
    		props로 넣어 준 값을 직접 전달해 줄 수 있음
    		color 값이 주어지지 않은 경우: blue를 기본 색상으로 설정함.
    	*/
    	background: $(props => props.color || 'blue';
    	padding: 1rem;
    	display: flex;
    `

    // 아래와 같이 JSX에서 props로 color을 전달해 줄 수 있음.
    <Box color="black">(...)</Box>
    ```

## props에 따른 조건부 스타일링

아래 코드와 같이 props를 참조한다면, 반드시 CSS로 감싸 주어서 Tagged 템플릿 리터럴을 사용해 줘야 함.

-   코드

    ```jsx
    		${(props) =>
            props.inverted &&
            css`
                background: none;
                border: 2px solid white;
                color: white;
                &:hover {
                    background: white;
                    color: black;
                }
            `};
    ```

## 반응형 디자인

styled-components를 사용할 때 반응형 디자인: 일반 CSS와 똑같이 media query 사용

-   코드

    ```jsx
    const Box = styled.div`
        /* props로 넣어준 값을 직접 전달해 줄 수 있음 */
        background: ${(props) => props.color || "blue"};
        padding: 1rem;
        display: flex;
        /* 
            기본적으로 가로 크기 1024px으로 두고 + 가운데 정렬,
            1024 px 미만일 경우에 768px으로 두고
            768 px 미만이 되면 꾁 채웁니다. */
        width: 1024px;
        margin: 0 auto;
        @media (max-width: 1024px) {
            width: 768px;
        }
        @media (max-width: 768px) {
            width: 100%;
        }
    `;
    ```

styled-components 메뉴얼에서 제공하는 유틸 함수를 사용하면 번거로움 ⬇️

-   유틸 함수 예제

    ```jsx
    const media = Object.keys(sizes).reduce((acc, label) => {
        // ? 열라 알 수 없음
        acc[label] = (...args) => css`
            @media (max-width: ${sizes[label] / 16}em) {
                ${css(...args)};
            }
        `;
        return acc;
    }, {});

    const Box = styled.div`
        /* props로 넣어준 값을 직접 전달해 줄 수 있음 */
        background: ${(props) => props.color || "blue"};
        padding: 1rem;
        display: flex;
        /* 
            기본적으로 가로 크기 1024px으로 두고 + 가운데 정렬,
            1024 px 미만일 경우에 768px으로 두고
            768 px 미만이 되면 꾁 채웁니다. */
        width: 1024px;
        margin: 0 auto;
        ${media.desktop`width: 768px;`};
        ${media.tablet`width: 100%;`}
    `;
    ```

# 9.5 정리

여기서 뭘 사용할 지는 너의 선택
