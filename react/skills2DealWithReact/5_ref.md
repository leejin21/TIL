> **ref** = HTML에서 id를 사용해 DOM 요소에 이름을 다는 것처럼 리액트 프로젝트 내부에서 DOM에 이름을 다는 방법

-   참고

    HTML에서 DOM 요소의 id는 유일(unique)해야 하는데 jsx에서 id를 달면 그대로 전달되어 문제가 생길 수 있음. ref는 id와 달리 컴포넌트 내부에서만 작동하기 때문에 중복 문제가 생기지 않음.

    대체로 id를 사용하지 않아도 되지만, 다른 라이브러리나 프레임워크와 함께 사용할 경우엔 id 뒷부분에 추가 텍스트를 붙여서 중복 id가 발생하지 않도록 해야 함(button01, button02, ...)

# 5.1 ref는 어떤 상황에서 사용해야 할까?

"DOM을 꼭 직접적으로 건드려야 하는 상황"에서 사용해야 함

-   예제 코드 (ValidationSample.js)

    ```jsx
    import React, { Component } from "react";
    import "./ValidationSample.css";

    class ValidationSample extends Component {
        state = {
            password: "",
            clicked: false,
            validated: false,
        };

        handleChange = (e) => {
            this.setState({ password: e.target.value });
            console.log(this.state);
        };

        handleButtonClick = () => {
            this.setState({
                clicked: true,
                validated: this.state.password === "0000",
            });
            console.log(this.state);
        };

        render() {
            return (
                <div>
                    <input
                        type="password"
                        value={this.state.password}
                        onChange={this.handleChange}
                        className={
                            this.state.clicked
                                ? this.state.validated
                                    ? "success"
                                    : "failure"
                                : ""
                        }
                    ></input>
                    <button onClick={this.handleButtonClick}>검증하기</button>
                </div>
            );
        }
    }

    export default ValidationSample;
    ```

-   예제 코드 (ValidationSample.css)

    ```jsx
    .success {
        background-color: lightgreen;
    }
    .failure {
        background-color: lightcoral;
    }
    ```

물론 위 예제 코드에서처럼 대부분의 상황에서는 state를 사용해서 필요한 기능을 구현할 수 있지만, 가끔 state만으로는 다음과 같이 해결할 수 없는 기능들이 있음.

-   특정 input에 포커스 주기
-   스크롤 박스 조작하기
-   Canvas 요소에 그림 그리기 등
-   참고

    함수형 컴포넌트: hook과 함께 씀(나중에 더 설명)

# 5.2 ref 사용

-   콜백 함수를 통한 ref 설정(가장 기본적인 방법)

    ```jsx
    <input
        ref={(ref) => {
            this.input = ref;
        }}
    />
    ```

-   createRef를 통한 ref 설정(v16.3~)

    ```jsx
    input = React.createRef();
    // 사용할 때: this.input.current 로 써야 함
    ```

-   앞서 말한 ref를 꼭 적용해야 하는 상황의 경우, 아래와 같이 ValidationSample.js를 변형할 수 있다.

    ```jsx
    /*
    		검증하기 버튼을 누르면 input 컴포넌트에 focus되도록
    		(검증하기 버튼에서 그대로 focus되지 않도록)
    		...은 중략 표시
    */
    class ValidationSample extends Component {
    		// ...
    	    handleButtonClick = () => {
    				// ...
            this.input.focus();
        };

        render() {
            return (
                <div>
                    <input
                        {/* ... */}
                        ref={(ref) => (this.input = ref)}
                    ></input>
                    {/* .... */}
                </div>
            );
        }
    }
    ```

# 5.3 컴포넌트에 ref 달기

컴포넌트 내부의 [DOM 요소](https://wit.nts-corp.com/2019/02/14/5522)를 컴포넌트 외부에서 사용할 때 씀.

-   사용법

    ```jsx
    <MyComponent
        ref={(ref) => {
            this.mycomp = ref;
        }}
    />
    ```

이러면 MyComponent 내부의 ref에도 접근 가능(예: mycomp.handleClick)

-   예제 코드(ScrollBox.js)

    ```jsx
    import React, { Component } from "react";

    class ScrollBox extends Component {
        scroll2Bottom = () => {
            const { scrollHeight, clientHeight } = this.box;
            // scrollHeight: 스크롤이 있는 박스 안(안 div)의 div 높이 = 650px
            // clientHeight: 스크롤이 있는 박스(밖 div)의 높이 = 300px
            this.box.scrollTop = scrollHeight - clientHeight;
            // scrollTop: 세로 스크롤바 위치(0~ 350)
        };
        render() {
            const style = {
                border: "1px solid black",
                height: "300px",
                width: "300px",
                overflow: "auto",
                position: "relative",
            };
            const innerStyle = {
                width: "100%",
                height: "650px",
                background: "linear-gradient(white, black)",
            };
            return (
                <div
                    style={style}
                    ref={(ref) => {
                        this.box = ref;
                    }}
                >
                    <div style={innerStyle}></div>
                </div>
            );
        }
    }

    export default ScrollBox;
    ```

    -   scrollTop이 왜 scrollHeight - clientHeight인 지

        ![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6c8cb3b8-d357-42a0-b04a-2b4ce844b785/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6c8cb3b8-d357-42a0-b04a-2b4ce844b785/Untitled.png)

-   예제 코드(App.js)

    ```jsx
    class App extends Component {
        render() {
            return (
                <div>
                    <ScrollBox ref={(ref) => (this.scrollbox = ref)} />
                    <button
                        onClick={() => {
                            this.scrollbox.scroll2Bottom();
                        }}
                    >
                        밑으로
                    </button>
                </div>
            );
        }
    }
    ```

    컴포넌트가 처음 렌더링될 때: this.scrollbox 값이 undefined이므로 this.scrollBox.scroll2Bottom 값을 읽어오는 과정에서 오류 발생

    -   ❓ 왜 컴포넌트가 처음 렌더링될 때 this.scrollbox의 값의 undefined인가

# 5.4 정리

그런데 이런 방식으로 프로젝트를 구현하는 것은 권장하지 않음. 컴포넌트끼리 서로 ref를 전달하고 전달받은 어떤 컴포넌트의 메서드를 ref를 통해 구현하는 방식은 스파게티 구조로 개발하게 되기 쉬움.

> 컴포넌트끼리 데이터를 교류할 때는 언제나 데이터를 부모 ↔ 자식 흐름으로 교류해야 함
