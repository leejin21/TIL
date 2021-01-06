> 이벤트 = 사용자가 웹 브라우저에서 DOM 요소들과 상호 작용하는 것

# 4.1 리액트의 이벤트 시스템

이벤트 종류는 여기 [링크](https://reactjs.org/docs/events.html) 확인하기(날 잡고 공부하기)

# 4.2 예제로 이벤트 핸들링 익히기

## onChange 이벤트 핸들링하기

-   예제

    ```jsx
    // EventPractice.js
    onChange={(e) => {
    		console.log(e);
    }}
    ```

e 객체는 SyntheticEvent로 웹 브라우저의 네이티브 이벤트를 감싸는 객체임

0.5초 뒤에 e 객체를 참조하면 e 객체 내부의 모든 값이 비워지게 됨

만약 비동기적으로 이벤트 객체를 참조할 일이 있다면 e.persist() 함수를 호출해주어야 함.

❓여기서 네이티브 이벤트 어쩌고가 뭐지

## 임의 메서드 만들기

-   예제

    ```jsx
    class EventPractice extends Component {
        state = {
            message: "",
        };
        constructor(props) {
            super(props);
            this.handleChange = this.handleChange.bind(this);
            this.handleClick = this.handleClick.bind(this);
        }
        handleChange(e) {
            this.setState({ message: e.target.value });
            console.log(e.target.value);
        }
        handleClick() {
            alert(this.state.message);
            this.setState({ message: "" });
        }
        render() {
            const { message } = this.state;
            return (
                <div>
                    <h1>이벤트 연습</h1>
                    <input
                        type="text"
                        name="message"
                        placeholder="아무거나 입력하기!"
                        value={this.state.message}
                        onChange={this.handleChange}
                    ></input>
                    <button onClick={this.handleClick}>MAKE EMPTY</button>
                </div>
            );
        }
    }
    ```

## input 여러 개 다루기

event 객체를 활용

-   예제

    ```jsx
    import React, { Component } from "react";

    class EventPractice extends Component {
        state = {
            username: "",
            message: "",
        };
        constructor(props) {
            super(props);
            this.handleChange = this.handleChange.bind(this);
            this.handleClick = this.handleClick.bind(this);
        }
        handleChange(e) {
            this.setState({ [e.target.name]: e.target.value });
            // console.log(this.state);
        }
        handleClick() {
            alert(this.state.message);
            this.setState({ message: "" });
        }
        render() {
            return (
                <div>
                    <h1>이벤트 연습</h1>
                    <input
                        type="text"
                        name="username"
                        placeholder="사용자 이름 입력하세요!"
                        value={this.state.username}
                        onChange={this.handleChange}
                    ></input>
                    <input
                        type="text"
                        name="message"
                        placeholder="메세지 입력하세요!"
                        value={this.state.message}
                        onChange={this.handleChange}
                    ></input>
                    <button onClick={this.handleClick}>MAKE EMPTY</button>
                </div>
            );
        }
    }

    export default EventPractice;
    ```

++ [객체 속 key](https://www.notion.so/key-5bdebc05d9ae425fb634071e14a0e818)

# 4.3 함수형 컴포넌트로 구현해 보기

-   예제

    ```jsx
    // * arrow ft 형태
    const EventPractice2 = () => {
        const [form, setForm] = useState({ username: "", message: "" });
        const handleChange = (e) => {
            // 다른 점
            setForm({ ...form, [e.target.name]: e.target.value });
        };
        const handleClick = () => {
            alert(form.username + ": " + form.message);
        };
        const handleEnter = (e) => {
            if (e.key === "Enter") {
                handleClick();
            }
        };
        return (
            <div>
                <h1>이벤트 연습하기 2</h1>
                <input
                    name="username"
                    value={form.username}
                    placeholder="사용자 이름을 입력해 주세요!"
                    onChange={handleChange}
                ></input>
                <input
                    name="message"
                    value={form.message}
                    placeholder="메세지를 입력해 주세요!"
                    onChange={handleChange}
                    onKeyPress={handleEnter}
                ></input>
                <button onClick={handleClick}>확인</button>
            </div>
        );
    };
    ```

# 4.4 정리

리액트를 사용하지 않고 그냥 쌩으로 html+css로 한번 해봐야 dom의 원리에 대해 더 이해할 수 있을 것 같음.
